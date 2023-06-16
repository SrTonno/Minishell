/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:04:39 by tvillare          #+#    #+#             */
/*   Updated: 2023/06/16 19:03:51 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*mov_to_next_list(t_list *list, int num)
{
	int	i;

	i = 0;
	while (num > i++)
		list = list->next;
	return (list);
}

static t_len_ast	count_blocks(t_list *list, int mode)
{
	t_len_ast	command;

	command.len = 1;
	command.meta = 0;
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
			command.meta++;
		command.len++;
		list = list->next;
	}
	return (command);
}

t_list	*create_new_node(t_list *token_lst, t_len_ast num, int i)
{
	t_ast_node	*ast_node;
	t_list		*new_node;

	ast_node = list_to_char(token_lst, num, i);
	if (ast_node == NULL)
		return (NULL);
	new_node = ft_lstnew(ast_node);
	if (new_node == NULL)
	{
		free_ast_node(ast_node);
		return (NULL);
	}
	return (new_node);
}

t_list	*add_new_node(t_list *token_lst, t_list **ast, t_len_ast num, int i)
{
	t_list		*new_node;

	new_node = create_new_node(token_lst, num, i);
	if (new_node == NULL)
		return (NULL);
	ft_lstadd_back(ast, new_node);
	return (new_node);
}

t_list	*parse(t_list *token_lst)
{
	t_list		*ast;
	t_len_ast	num;
	int			index;
	//t_list		*new_node;

	ast = NULL;
	index = 0;
	num = count_blocks(token_lst, 0);
	if (add_new_node(token_lst, &ast, num, index++) == NULL)
		return (NULL);
	token_lst = mov_to_next_list(token_lst, num.len);
	while (token_lst != NULL)
	{
		num = count_blocks(token_lst, 0);
		if (*((unsigned char *)token_lst->content) != '|')
		{
			if (add_new_node(token_lst, &ast, num, index++) == NULL)
			{
				ft_lstclear(&ast, free_ast_node);
				return (NULL);
			}
		}
		token_lst = mov_to_next_list(token_lst, num.len);
	}
	return (ast);
}
