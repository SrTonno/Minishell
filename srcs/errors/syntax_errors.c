/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:58:15 by javmarti          #+#    #+#             */
/*   Updated: 2023/04/24 17:58:15 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_msg.h"

int	check_syntax_metachars(t_list *token_lst)
{
	char	*c;

	while (token_lst)
	{
		c = token_lst->content;
		if (is_special(*c))
		{
			if (*c == '|' && ft_strlen(c) != 1)
				return (error_msg(SYNTAX_ERROR, c + 1));
			else if ((*c == '<' || *c == '>')
				&& ft_strlen(c) == 2 && *c != *(c + 1))
				return (error_msg(SYNTAX_ERROR, c + 1));
			else if ((*c == '<' || *c == '>') && ft_strlen(c) > 2)
				return (error_msg(SYNTAX_ERROR, c + 2));
		}
		token_lst = token_lst->next;
	}
	return (0);
}

int	check_syntax_after_metachars(t_list *token_lst)
{
	char	*c;

	while (token_lst)
	{
		c = token_lst->content;
		if (*c == '|')
		{
			if (token_lst->next == NULL)
				return (error_msg(SYNTAX_ERROR, NULL));
			if (*(char *)token_lst->next->content == '|')
				return (error_msg(SYNTAX_ERROR, token_lst->next->content));
		}
		else if (*c == '<' || *c == '>')
		{
			if (token_lst->next == NULL)
				return (error_msg(SYNTAX_ERROR, NULL));
			else if (is_special(*(char *)token_lst->next->content))
				return (error_msg(SYNTAX_ERROR, token_lst->next->content));
		}
		token_lst = token_lst->next;
	}
	return (0);
}

