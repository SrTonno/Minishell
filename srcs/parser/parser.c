/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:04:39 by tvillare          #+#    #+#             */
/*   Updated: 2023/03/10 16:25:11 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	count_blocks(t_list *list, int mode)
{
	int	command;

	command = 1;
	while (list->next != NULL)
	{
		if (*((unsigned char *)list->content) == '|'
			|| *((unsigned char *)list->content) == '<'
			|| (*((unsigned char *)list->content) == '>') || mode == 1)
		{
			if (command == 1)
				return (command);
			return (command - 1);
		}
		command++;
		list = list->next;
	}
	if ((*((unsigned char *)list->content) == '|'
			|| *((unsigned char *)list->content) == '<'
			|| (*((unsigned char *)list->content) == '>')) && command != 1)
		return (command - 1);
	return (command);
}

static t_ast_node	*list_to_char(t_list *list, int max)
{
	int			i;
	t_ast_node	*new_ast;

	i = 0;
	new_ast = ft_calloc(1, sizeof(t_ast_node));
	new_ast->command = ft_calloc(max + 1, sizeof(char *));
	while (max > i)
	{
		new_ast->command[i] = (char *)list->content;
		i++;
		list = list->next;
	}
	new_ast->next = NULL;
	return (new_ast);
}

static void	new_block_ast(t_ast_node *ast, t_list *list, int max)
{
	ast = find_end_ast(ast);
	ast->next = list_to_char(list, max);
}

static int	find_heredocs(t_ast_node *ast, int num)
{
	int	len;
	int	i;

	i = -1;
	ast = find_end_ast(ast);
	len = ft_strlen(ast->command[num - 1]);
	while (ast->command[num - 1][++i] != '\0' && len >= 2)
	{
		if (len > i + 1
			&& (ast->command[num - 1][i] == '<'
			&& ast->command[num - 1][i +1] == '<'))
			return (1);
	}
	return (0);
}

t_ast_node	*parser(t_list *list)
{
	t_ast_node	*ast;
	int			num;

	num = count_blocks(list, 0);
	ast = list_to_char(list, num);
	list = mov_to_next_list(list, num);
	while (list != NULL)
	{
		num = count_blocks(list, find_heredocs(ast, num));
		new_block_ast(ast, list, num);
		list = mov_to_next_list(list, num);
	}
	return (ast);
}
