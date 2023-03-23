/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:04:39 by tvillare          #+#    #+#             */
/*   Updated: 2023/03/23 17:57:07 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_len_ast	count_blocks(t_list *list, int mode)
{
	t_len_ast	command;

	command.len = 1;
	command.meta = 0;
	command.heredocs = 0;
	while (list->next != NULL)
	{
		if (*((unsigned char *)list->content) == '|')
		{
			if (command.len != 1)
				command.len--;
			return (command);
		}
		if (*((unsigned char *)list->content) == '<'
			|| (*((unsigned char *)list->content) == '>') || mode == 1)
		{
			if (*((unsigned char *)list->content) == '<'
				&& ft_strlen(list->content) == 2)
				command.heredocs++;
			command.meta++;
		}
		command.len++;
		list = list->next;
	}
	return (command);
}
	/*if ((*((unsigned char *)list->content) == '|'
			|| *((unsigned char *)list->content) == '<'
			|| (*((unsigned char *)list->content) == '>')) && command.len != 1)
			{
				command.meta++;
				command.len--;
			}*/

static void	new_block_ast(t_ast_node *ast, t_list *list, t_len_ast max)
{
	ast = find_end_ast(ast);
	ast->next = list_to_char(list, max);
}
/*
static int	find_heredocs(t_ast_node *ast, t_len_ast num)
{
	int	i;

	i = -1;
	ast = find_end_ast(ast);
	while (ast->command[num.len - 1][++i] != '\0')
	{
		if ((ast->command[num.len - 1][i] == '<'
			|| ast->command[num.len - 1][i] == '>'))
			return (1);
	}
	return (0);
}*/

t_ast_node	*parser(t_list *token_lst)
{
	t_ast_node	*ast;
	t_len_ast	num;

	if (check_metachars(token_lst) != 0
		|| check_text_after_metachars(token_lst) != 0
		|| check_files(token_lst) != 0)
		return (NULL);
	num = count_blocks(token_lst, 0);
	ast = list_to_char(token_lst, num);
	token_lst = mov_to_next_list(token_lst, num.len);
	while (token_lst != NULL)
	{
		num = count_blocks(token_lst, 0);
		new_block_ast(ast, token_lst, num);
		token_lst = mov_to_next_list(token_lst, num.len);
	}
	return (ast);
}
