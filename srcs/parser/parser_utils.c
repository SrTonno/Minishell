/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:45:55 by tvillare          #+#    #+#             */
/*   Updated: 2023/03/31 18:12:48 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*find_end_ast(t_ast_node *ast)
{
	while (ast->next != NULL)
		ast = ast->next;
	return (ast);
}

t_list	*mov_to_next_list(t_list *list, int num)
{
	int	i;

	i = 0;
	while (num > i++)
		list = list->next;
	return (list);
}

void	free_ast(t_ast_node *ast)
{
	t_ast_node	*aux;

	while (ast != NULL)
	{
		aux = ast->next;
		if (ast->input_fd != STDIN_FILENO)
			close(ast->input_fd);
		if (ast->output_fd != STDOUT_FILENO)
			close(ast->output_fd);
		if (ast->heredocs != NULL)
			free(ast->heredocs);
		free(ast->command);
		free(ast->pipe_fd);
		free(ast);
		ast = aux;
	}
	return ;
}
