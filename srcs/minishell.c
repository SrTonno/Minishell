/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:36:08 by javmarti          #+#    #+#             */
/*   Updated: 2023/03/07 15:36:08 by javmarti         ###   ########.fr       */
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

void	ast_node_free(void *ptr)
{
	t_ast_node	*ast_node;

	ast_node = (t_ast_node *)ptr;
	free_split(ast_node->command);
	ft_lstclear(&ast_node->redir, redir_free);
	free(ast_node);
	return ;
}

static void	all_free(t_list *token_lst, t_list *ast, char *input)
{
	ft_lstclear(&token_lst, free);
	ft_lstclear(&ast, ast_node_free);
	free(input);
}

int	main(int argc, char *argv[], char **env)
{
	char				*input;
	char				**new_env;
	struct sigaction	sa;
	int					status;

	if (argc != 1)
		return (0);
	(void)argc;
	(void)argv;
	env = malloc_env(env);
	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(2, &sa, NULL) == -1 || sigaction(3, &sa, NULL) == -1)
		printf("Error\n");
	input = argv[0];
	status = 0;
	while (1)
	{
		input = readline(PROMPT);
		ctr_d(input, NULL);
		if (ft_strncmp(input, "exit", 5) == 0)
			break ;
		if (ft_strncmp(input, "\0", 1) == 0)
			continue ;
		add_history(input);
		status = handle_input(input, env);
		if (status == -1)
			return (0);
	}
	free(input);
	return (0);
}

int	check_quotes(char *input)
{
	char	*end_quote;

	while (*input)
	{
		if (*input == DOUBLE_QUOTE || *input == SINGLE_QUOTE)
		{
			end_quote = ft_strchr(input + 1, *input);
			if (end_quote == NULL)
				return (syntax_error(NULL));
			input = end_quote + 1;
		}
		input++;
	}
	return (0);
}

int	handle_input(char *input, char *env[])
{
	t_list	*token_lst;
	t_list	*ast;
	int		status; // exit code del ultimo comando -> $?

	if (check_quotes(input) != 0)
	{
		free(input);
		return (2);
	}
	while (find_var(input) >= 0)
		input = env_expand(env, input);
	// printf("input = %s\n", input);
	token_lst = tokenize(input);
	free(input);
	if (token_lst == NULL)
		return (malloc_error()); // crear errors.h con fatal error para malloc/fork/execve...
	if (check_syntax_metachars(token_lst) != 0
		|| check_syntax_after_metachars(token_lst) != 0)
	{
		ft_lstclear(&token_lst, free);
		return (2);
	}
	print_lst(token_lst);
	// ast = parse(token_lst);
	// ft_lstclear(&token_lst, free);
	// if (ast == NULL)
	// 	return (0);
	// // print_ast(ast);
	// status = execute(ast, env);
	// all_free(token_lst, ast, input);
	return (0);
}
