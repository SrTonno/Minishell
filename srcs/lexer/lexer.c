/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:19:08 by javmarti          #+#    #+#             */
/*   Updated: 2023/03/07 19:19:08 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_list	*tokenize(char *inputLine)
{
	t_lexer	lexer;

	lexer = init_lexer(inputLine);
	while (lexer.str[lexer.index] != '\0')
	{
		while (is_space(lexer.str[lexer.index]))
		{
			if (lexer.str[lexer.index++] == '\0')
				return (lexer.token_lst);
		}
		lexer.token_start = lexer.str + lexer.index;
		while (is_space(lexer.str[lexer.index]) == 0)
		{
			if (handle_char(&lexer) == -1)
				return (NULL);
		}
		if (lexer.str + lexer.index - lexer.token_start > 0
				&& add_new_token_lst(&lexer) == -1)
			return (NULL);
	}
	return (lexer.token_lst);
}
