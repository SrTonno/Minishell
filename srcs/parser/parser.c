/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:04:39 by tvillare          #+#    #+#             */
/*   Updated: 2023/04/19 16:59:42 by javmarti         ###   ########.fr       */
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

t_list	*create_new_node(t_list *token_lst, t_len_ast num)
{
	t_ast_node	*ast_node;
	t_list		*new_node;

	ast_node = list_to_char(token_lst, num);
	if (ast_node == NULL)
		return (NULL);
	new_node = ft_lstnew(ast_node);
	if (new_node == NULL)
	{
		ast_node_free(ast_node);
		return (NULL);
	}
	return (new_node);
}

t_list	*parse(t_list *token_lst)
{
	t_list		*ast;
	t_list		*new_node;
	t_len_ast	num;

	ast = NULL;
	num = count_blocks(token_lst, 0);
	new_node = create_new_node(token_lst, num);
	if (new_node == NULL)
		return (NULL);
	ft_lstadd_back(&ast, new_node);
	token_lst = mov_to_next_list(token_lst, num.len);
	while (token_lst != NULL)
	{
		num = count_blocks(token_lst, 0);
		if (*((unsigned char *)token_lst->content) != '|')
		{
			new_node = create_new_node(token_lst, num);
			if (new_node == NULL)
			{
				ft_lstclear(&ast, ast_node_free);
				return (NULL);
			}
			ft_lstadd_back(&ast, new_node);
		}
		token_lst = mov_to_next_list(token_lst, num.len);
	}
	return (ast);
}
