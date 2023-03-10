/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:45:55 by tvillare          #+#    #+#             */
/*   Updated: 2023/03/10 15:29:10 by tvillare         ###   ########.fr       */
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
