/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:36:08 by javmarti          #+#    #+#             */
/*   Updated: 2023/04/14 18:01:03 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lst(t_list *lst)
{
	while (lst != NULL)
	{
		printf("%s\n", (char *) lst->content);
		lst = lst->next;
	}
	return ;
}

static	void print_ast(t_list *ast)
{
	int	i;
	int	index = 1;
	t_ast_node *ast_node;
	t_redir_type *redir;

	while(ast != NULL)
	{
		ast_node = (t_ast_node *)ast->content;
		printf("NODO AST Nº%i\n", index++);
		printf("---------------------------------------------\ncommandos: ");
		i = -1;
		while (ast_node->command[++i] != NULL)
			printf("%s ", ast_node->command[i]);
		printf("\narchivos y heredocs:\n");
		while (ast_node->redir != NULL)
		{
			redir = (t_redir_type *)ast_node->redir->content;
			printf("%s -> %i\n", redir->text, redir->type);
			ast_node->redir = ast_node->redir->next;
		}
		ast = ast->next;
	}
}

void	redir_free(void *ptr)
{
	t_redir_type	*redir;

	redir = (t_redir_type *)ptr;
	free(redir->text);
	free(redir);
	return ;
}

void	free_ast_node(void *ptr)
{
	t_ast_node	*ast_node;

	ast_node = (t_ast_node *)ptr;
	free_split(ast_node->command);
	free(ast_node->pipe_fd);
	free(ast_node->binary);
	ft_lstclear(&ast_node->redir, redir_free);
	free(ast_node);
	return ;
}

void	leaks()
{
	system("leaks -q minishell");
}

int	main(int argc, char *argv[], char **env)
{
	char				*input;
	struct sigaction	sa;

	// atexit(leaks);
	if (argc != 1)
		return (0);
	env = malloc_env(env);
	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(2, &sa, NULL) == -1 || sigaction(3, &sa, NULL) == -1)
		printf("Error\n");
	loop(env);
	return (0);
}

void	loop(char **env)
{
	int		status;
	char	*input;

	status = 0;
	while (1)
	{
		input = readline(PROMPT);
		ctr_d(input, NULL);
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			free_split(env);
			break ;
		}
		if (ft_strncmp(input, "\0", 1) == 0)
		{
			free(input);
			continue ;
		}
		add_history(input);
		status = handle_input(input, &env, status);
		if (status == -1)
			break ;
	}
	free(input);
}

int	clean_input(char **input, char ***env, int status)
{
	if (check_quotes(*input) != 0)
	{
		free(*input);
		return (2);
	}
	while (find_var(*input) >= 0)
	{
		*input = env_expand(env, *input, status);
		if (*input == NULL)
			return (error_msg(MALLOC_ERROR, NULL));
	}
	// *input = remove_quotes(*input);
	// if (*input == NULL)
	// 	return (error_msg(MALLOC_ERROR, NULL));
	return (0);
}

int	tokenize_and_parse(char *input, t_list **ast)
{
	t_list	*token_lst;

	token_lst = tokenize(input);
	free(input);
	if (token_lst == NULL)
		return (error_msg(MALLOC_ERROR, NULL));
	if (check_syntax_metachars(token_lst) != 0
		|| check_syntax_after_metachars(token_lst) != 0)
	{
		ft_lstclear(&token_lst, free);
		return (2);
	}
	// print_lst(token_lst);
	*ast = parse(token_lst);
	ft_lstclear(&token_lst, free);
	if (*ast == NULL)
		return (error_msg(MALLOC_ERROR, NULL));
	// print_ast(ast);
	return (0);
}

int	handle_input(char *input, char **env[], int status)
{
	t_list	*ast;

	status = clean_input(&input, env, status);
	if (status == -1 || status == 2)
		return (status);
	status = tokenize_and_parse(input, &ast);
	if (status == -1 || status == 2)
		return (status);
	status = execute(ast, env);
	ft_lstclear(&ast, free_ast_node);
	return (status);
}
