/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:24:15 by tvillare          #+#    #+#             */
/*   Updated: 2023/04/09 22:40:34 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	find_null(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

static void	check_redirect(t_ast_node *ast, t_list *list)
{
	if (*((unsigned char *)list->content) == '<')
	{
		if (ft_strlen((char *)list->content) == 2)
			ast->heredocs[find_null(ast->heredocs)]
				= ft_strjoin(list->next->content, "\n");
		if (ast->input_fd != STDIN_FILENO)
			close(ast->input_fd);
		ast->input_fd = open(list->next->content, O_RDONLY);
	}
	if (*((unsigned char *)list->content) == '>')
	{
		if (ft_strlen((char *)list->content) == 2)
			ast->mode_write = APPEND;
		else
			ast->mode_write = OVERWRITE;
		if (ast->output_fd != STDOUT_FILENO)
			close(ast->output_fd);
		ast->output_fd = open(list->next->content, O_WRONLY);
	}
}

static t_ast_node	*create_ast(t_len_ast max)
{
	t_ast_node	*new_ast;

	new_ast = ft_calloc(1, sizeof(t_ast_node));
	new_ast->command = ft_calloc((max.len - (max.meta * 2)) + 1, \
	sizeof(char *));
	new_ast->binary = NULL;
	new_ast->heredocs = ft_calloc(max.heredocs + 1, sizeof(char *));
	new_ast->input_fd = STDIN_FILENO;
	new_ast->output_fd = STDOUT_FILENO;
	new_ast->mode_write = NOFILE;
	new_ast->pipe_fd = NULL;
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
