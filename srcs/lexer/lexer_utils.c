/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:24:19 by javmarti          #+#    #+#             */
/*   Updated: 2023/04/25 19:24:19 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	init_lexer(char *inputLine)
{
	t_lexer	lexer;

	lexer.str = inputLine;
	lexer.len = ft_strlen(inputLine);
	lexer.index = 0;
	lexer.token_lst = NULL;
	lexer.token_len = 0;
	return (lexer);
}

int	add_new_token_lst(t_lexer *lexer)
{
	char	*token;

	lexer->token_len = (size_t)(lexer->str + lexer->index - lexer->token_start);
	if (lexer->token_len <= 0)
		return (0);
	token = (char *)ft_calloc(lexer->token_len + 1, sizeof(char));
	if (token == NULL)
	{
		ft_lstclear(&lexer->token_lst, free);
		return (-1);
	}
	ft_strlcpy(token, lexer->token_start, lexer->token_len + 1);
	ft_lstadd_back(&lexer->token_lst, ft_lstnew((void *)token));
	return (0);
}

int	is_quote(char c)
{
	if (c == SINGLE_QUOTE || c == DOUBLE_QUOTE)
		return (1);
	return (0);
}
