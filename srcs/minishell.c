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

static	void print_ast(t_ast_node *ast)
{
	int	i;
	int	index = 1;

	while(ast != NULL)
	{
		printf("NODO AST Nº%i\n", index++);
		printf("---------------------------------------------\ncommandos: ");
		i = -1;
		while (ast->command[++i] != NULL)
			printf("%s ", ast->command[i]);
		i = -1;
		printf("\nheredocs: ");
		while (ast->heredocs[++i] != NULL)
			printf("%s ", ast->heredocs[i]);
		printf("\ninfile: %i/ outfile: %i mode %i", ast->input_fd, ast->output_fd, ast->mode_write);
		printf("\n---------------------------------------------\n");
		ast = ast->next;
	}
}

static void	all_free(t_list *token_lst, t_ast_node *ast, char *input)
{
	ft_lstclear(&token_lst, free);
	if (ast != NULL)
		free_ast(ast);
	free(input);
}

int	main(int argc, char *argv[], char **env)
{
	char				*input;
	char				**new_env;
	struct sigaction	sa;

	if (argc != 1)
		return (0);
	(void)argc;
	(void)argv;
	//env = malloc_env(env);
	env = malloc_env(env);
	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(2, &sa, NULL) == -1 || sigaction(3, &sa, NULL) == -1)
		printf("Error\n");
	input = argv[0];
	while (1)
	{
		input = readline(PROMPT);
		ctr_d(input, NULL);
		if (ft_strncmp(input, "exit", 5) == 0)
			break ;
		if (ft_strncmp(input, "\0", 1) == 0)
			continue ;
		add_history(input);
		if (handle_input(input, env) == -1)
			return (0);
	}
	free(input);
	return (0);
}

int	handle_input(char *input, char *env[])
{
	t_list		*token_lst;
	t_ast_node	*ast;
	int			status; // exit code del ultimo comando -> $?

	while (find_var(input) >= 0)
		input = env_expand(env, input);
	printf("input = %s\n", input);
	token_lst = tokenize(input);
	if (token_lst == NULL)
		return (-1);
	// print_lst(token_lst);
	ast = parse(token_lst);
	if (ast == NULL)
	{
		all_free(token_lst, ast, input);
		return (-1);
	}
	// print_ast(ast);
	status = execute(ast, env);
	// all_free(token_lst, ast, input);
	return (0);
}
