/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:24:15 by tvillare          #+#    #+#             */
/*   Updated: 2023/03/23 18:11:24 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	find_null(char **str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static void	check_redirect(t_ast_node *ast, t_list *list)
{
	if (*((unsigned char *)list->content) == '<')
	{
		if (ft_strlen((char *)list->content) == 2)
			ast->heredocs[find_null(ast->heredocs)] = list->next->content;
		if (ast->output_fd != 0)
			close(ast->output_fd);
		ast->output_fd = open(list->next->content, O_RDONLY, 0);
	}
	if (*((unsigned char *)list->content) == '>')
	{
		if (ft_strlen((char *)list->content) == 2)
			ast->mode_write = 2;
		else
			ast->mode_write = 1;
		if (ast->input_fd != 0)
			close(ast->input_fd);
		ast->input_fd = open(list->next->content, O_RDWR | O_CREAT, 0644);
	}
}

static t_ast_node	*create_ast(t_len_ast max)
{
	t_ast_node	*new_ast;

	new_ast = ft_calloc(1, sizeof(t_ast_node));
	new_ast->command = ft_calloc((max.len - (max.meta * 2)) + 1, \
	sizeof(char *));
	new_ast->heredocs = ft_calloc(max.heredocs + 1, sizeof(char *));
	new_ast->input_fd = 0;
	new_ast->output_fd = 0;
	new_ast->mode_write = 0;
	return (new_ast);
}

t_ast_node	*list_to_char(t_list *list, t_len_ast max)
{
	int			i;
	int			extra;
	t_ast_node	*new_ast;

	i = 0;
	extra = 0;
	new_ast = create_ast(max);
	while ((max.len) > i + extra)
	{
		check_redirect(new_ast, list);
		if (*((unsigned char *)list->content) == '>'
			|| *((unsigned char *)list->content) == '<')
		{
			extra = extra + 2;
			list = list->next;
		}
		else
			new_ast->command[i++] = (char *)list->content;
		list = list->next;
	}
	new_ast->next = NULL;
	return (new_ast);
}
