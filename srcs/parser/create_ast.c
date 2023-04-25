/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:24:15 by tvillare          #+#    #+#             */
/*   Updated: 2023/04/25 19:58:54 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*create_redir(char *text, int type)
{
	t_redir_type	*redir;
	t_list			*new_node;

	if (text == NULL)
		return (NULL);
	redir = (t_redir_type *)ft_calloc(1, sizeof(t_redir_type));
	if (redir == NULL)
		return (NULL);
	redir->text = ft_strdup(text);
	if (redir->text == NULL)
	{
		free(redir);
		return (NULL);
	}
	redir->type = type;
	new_node = ft_lstnew(redir);
	if (new_node == NULL)
		redir_free(redir);
	return (new_node);
}

static int	store_redir(t_ast_node *ast, t_list *list)
{
	t_list	*redir;

	if (*((unsigned char *)list->content) == '<')
	{
		if (ft_strlen((char *)list->content) == 1)
			redir = create_redir(list->next->content, INFILE);
		else
		{
			redir = create_redir(ft_strjoin(list->next->content, "\n"),
					HEREDOC);
		}
	}
	else
	{
		if (ft_strlen((char *)list->content) == 1)
			redir = create_redir(list->next->content, OVERWRITE);
		else
			redir = create_redir(list->next->content, APPEND);
	}
	if (redir == NULL)
		return (-1);
	ft_lstadd_back(&ast->redir, redir);
	return (0);
}

static t_ast_node	*create_ast_node(t_len_ast max)
{
	t_ast_node	*new_ast;

	new_ast = ft_calloc(1, sizeof(t_ast_node));
	new_ast->command = ft_calloc((max.len - (max.meta * 2)) + 1, \
		sizeof(char *));
	if (new_ast == NULL)
		return (NULL);
	new_ast->redir = NULL;
	new_ast->binary = NULL;
	new_ast->input_fd = 0;
	new_ast->output_fd = 1;
	new_ast->pipe_fd = NULL;
	return (new_ast);
}

t_ast_node	*fill_ast_node(t_list **token_lst, t_ast_node *new_ast,
	int *i, int *extra)
{
	if (*((unsigned char *)(*token_lst)->content) == '>'
		|| *((unsigned char *)(*token_lst)->content) == '<')
	{
		if (store_redir(new_ast, *token_lst) == -1)
		{
			ast_node_free(new_ast);
			return (NULL);
		}
		*extra += 2;
		(*token_lst) = (*token_lst)->next;
	}
	else
	{
		new_ast->command[*i] = ft_strdup((*token_lst)->content);
		if (new_ast->command[(*i)++] == NULL)
		{
			ast_node_free(new_ast);
			return (NULL);
		}
	}
}

t_ast_node	*list_to_char(t_list *token_lst, t_len_ast max)
{
	int			i;
	int			extra;
	t_ast_node	*new_ast;

	i = 0;
	extra = 0;
	new_ast = create_ast_node(max);
	if (new_ast == NULL)
		return (NULL);
	while ((max.len) > i + extra)
	{
		if (fill_ast_node(&token_lst, new_ast, &i, &extra) == NULL)
			return (NULL);
		token_lst = token_lst->next;
	}
	return (new_ast);
}
