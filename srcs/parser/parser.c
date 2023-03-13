/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:04:39 by tvillare          #+#    #+#             */
/*   Updated: 2023/03/13 23:22:18 by javmarti         ###   ########.fr       */
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
	int	i;

	i = -1;
	ast = find_end_ast(ast);
	while (ast->command[num - 1][++i] != '\0')
	{
		if ((ast->command[num - 1][i] == '<'
			|| ast->command[num - 1][i] == '>'))
			return (1);
	}
	return (0);
}

t_ast_node	*parser(t_list *token_lst)
{
	t_ast_node	*ast;
	int			num;

	if (check_metachars(token_lst) != 0
		|| check_text_after_metachars(token_lst) != 0
		|| check_files(token_lst) != 0)
		return (NULL);
	num = count_blocks(token_lst, 0);
	ast = list_to_char(token_lst, num);
	token_lst = mov_to_next_list(token_lst, num);
	while (token_lst != NULL)
	{
		num = count_blocks(token_lst, find_heredocs(ast, num));
		new_block_ast(ast, token_lst, num);
		token_lst = mov_to_next_list(token_lst, num);
	}
	return (ast);
}
