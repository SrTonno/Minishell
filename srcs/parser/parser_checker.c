/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 21:45:20 by javmarti          #+#    #+#             */
/*   Updated: 2023/03/11 21:45:20 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_metachars(t_list *token_lst)
{
	char	*c;

	while (token_lst)
	{
		c = token_lst->content;
		if (is_special(*c))
		{
			if (*c == '|' && ft_strlen(c) != 1)
				return (handle_error(SYNTAX_ERROR, c + 1));
			else if ((*c == '<' || *c == '>')
				&& ft_strlen(c) == 2 && *c != *(c + 1))
				return (handle_error(SYNTAX_ERROR, c + 1));
			else if ((*c == '<' || *c == '>') && ft_strlen(c) > 2)
				return (handle_error(SYNTAX_ERROR, c + 2));
		}
		token_lst = token_lst->next;
	}
	return (0);
}

int	check_text_after_metachars(t_list *token_lst)
{
	char	*c;

	while (token_lst)
	{
		c = token_lst->content;
		if (*c == '|')
		{
			if (token_lst->next == NULL)
				return (handle_error(SYNTAX_ERROR, NULL));
			if (*(char *)token_lst->next->content == '|')
				return (handle_error(SYNTAX_ERROR, token_lst->next->content));
		}
		else if (*c == '<' || *c == '>')
		{
			if (token_lst->next == NULL)
				return (handle_error(SYNTAX_ERROR, NULL));
			else if (is_special(*(char *)token_lst->next->content))
				return (handle_error(SYNTAX_ERROR, token_lst->next->content));
		}
		token_lst = token_lst->next;
	}
	return (0);
}

t_list	*jump_next_pipe(t_list *token_lst)
{
	while (token_lst->next)
	{
		if (*(char *)token_lst->content == '|')
			break ;
		token_lst = token_lst->next;
	}
	return (token_lst);
}

int	check_files(t_list *token_lst)
{
	int	count;

	count = 0;
	while (token_lst)
	{
		if (ft_strncmp(token_lst->content, "<", 2) == 0)
		{
			if (access(token_lst->next->content, R_OK) == -1)
			{
				count = handle_error(NO_FILE_ERROR, token_lst->next->content);
				token_lst = jump_next_pipe(token_lst);
			}
		}
		else if (*(char *)token_lst->content == '>')
		{
			if (access(token_lst->next->content, F_OK) == 0
				&& access(token_lst->next->content, W_OK) == -1)
			{
				count = handle_error(PERM_ERR, token_lst->next->content);
				token_lst = jump_next_pipe(token_lst);
			}
		}
		token_lst = token_lst->next;
	}
	return (count);
}
