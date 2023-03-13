/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:45:55 by tvillare          #+#    #+#             */
/*   Updated: 2023/03/13 23:26:26 by javmarti         ###   ########.fr       */
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

	while (ast)
	{
		aux = ast->next;
		free(ast);
		ast = aux;
	}
	return ;
}
