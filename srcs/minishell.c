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
		while (ast->heredocs[++i] != '\0')
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

int	main(void)
{
	char				*input;
	struct sigaction	sa;
	t_list				*token_lst;
	t_ast_node			*ast;

	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(2, &sa, NULL) == -1 || sigaction(3, &sa, NULL) == -1)
		printf("Error\n");
	while (1)
	{
		input = readline(PROMPT);
		ctr_d(input);
		if (ft_strncmp(input, "exit", 5) == 0)
			break ;
		if (ft_strncmp(input, "\0", 1) == 0)
			continue ;
		add_history(input);
		token_lst = tokenize(input);
		if (token_lst == NULL)
			break ;
		//print_lst(token_lst);
		ast = parse(token_lst);
		print_ast(ast);
		all_free(token_lst, ast, input);
	}
	free(input);
	return (0);
}
