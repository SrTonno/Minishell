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

int	add_new_token_lst(t_lexer *lexer, int type)
{
	t_token	*token;
	t_list	*new_node;

	lexer->token_len = (size_t)(lexer->str + lexer->index - lexer->token_start);
	if (lexer->token_len <= 0)
		return (0);
	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (-1);
	token->token = (char *)ft_calloc(lexer->token_len + 1, sizeof(char));
	if (token->token == NULL)
	{
		free(token);
		return (-1);
	}
	ft_strlcpy(token->token, lexer->token_start, lexer->token_len + 1);
	token->token_type = type;
	new_node = ft_lstnew((void *)token);
	if (new_node == NULL)
		return (-1);
	ft_lstadd_back(&lexer->token_lst, new_node);
	return (0);
}

char	*append_text(char *dst, char *src, size_t size)
{
	char	*aux_text;
	char	*new_token;

	if (dst == NULL || size == 0)
		return (dst);
	aux_text = (char *)ft_calloc(size + 1, sizeof(char));
	if (aux_text == NULL)
		return (NULL);
	ft_strlcat(aux_text, src, size + 1);
	new_token = ft_strjoin(dst, aux_text);
	free(dst);
	free(aux_text);
	if (new_token == NULL)
		return (NULL);
	return (new_token);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

char	*create_token(t_lexer *lexer, int *heredoc_flag)
{
	char	*token;

	token = (char *)ft_calloc(2, sizeof(char));
	if (token != NULL && *heredoc_flag == 1)
	{
		token[0] = '"';
		*heredoc_flag = 0;
	}
	token = append_text(token, lexer->token_start,
			lexer->index - (lexer->token_start - lexer->str));
	lexer->token_start = lexer->str + lexer->index;
	return (token);
}
