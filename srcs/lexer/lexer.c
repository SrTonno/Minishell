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

t_list	*tokenize(char *_lexer)
{
	t_lexer	lexer;

	lexer = init_lexer(_lexer);
	while (lexer.str[lexer.index] != '\0')
	{
		while (is_space(lexer.str[lexer.index]))
		{
			if (lexer.str[lexer.index] == '\0')
				return (lexer.token_lst);
			lexer.index++;
		}
		lexer.token_start = lexer.str + lexer.index;
		while (is_space(lexer.str[lexer.index]) == 0)
			handle_char(&lexer);
		if (add_new_token_lst(&lexer) == -1)
			return (NULL);
	}
	return (lexer.token_lst);
}
