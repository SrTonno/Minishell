/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:44:35 by javmarti          #+#    #+#             */
/*   Updated: 2023/03/08 19:44:35 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	handle_special(t_lexer *lexer);
static int	handle_quotation_marks(t_lexer *lexer);

int	handle_char(t_lexer *lexer)
{
	char	*curr_char;

	curr_char = lexer->str + lexer->index;
	if (*curr_char == '\'' || *curr_char == '"')
	{
		if (handle_quotation_marks(lexer) == -1)
		{
			ft_lstclear(&lexer->token_lst, free);
			return (-1);
		}
	}
	if (is_special(*curr_char))
	{
		if (handle_special(lexer) == -1)
		{
			ft_lstclear(&lexer->token_lst, free);
			return (-1);
		}
	}
	else
		lexer->index++;
	return (0);
}

static int	handle_special(t_lexer *lexer)
{
	if (lexer->str + lexer->index - lexer->token_start > 0
		&& add_new_token_lst(lexer) == -1)
		return (-1);
	lexer->token_start = lexer->str + lexer->index;
	while (is_special(lexer->str[lexer->index]))
		lexer->index++;
	if (add_new_token_lst(lexer) == -1)
		return (-1);
	lexer->token_start = lexer->str + lexer->index;
	return (0);
}

static int	handle_quotation_marks(t_lexer *lexer)
{
	char	*end_quote;
	char	quote;

	quote = lexer->str[lexer->index];
	end_quote = ft_strchr(lexer->str + lexer->index + 1, quote);
	if (lexer->str + lexer->index - lexer->token_start > 0
		&& add_new_token_lst(lexer) == -1)
		return (-1);
	lexer->token_start = lexer->str + lexer->index + 1;
	lexer->index = end_quote - lexer->str;
	if (*lexer->token_start == '\0')
		return (0);
	if (add_new_token_lst(lexer) == -1)
		return (-1);
	lexer->index++;
	lexer->token_start = lexer->str + lexer->index;
	return (0);
}
