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

static int	handle_special(t_lexer *lexer, int *heredoc_flag);
static int	handle_quotation_marks(t_lexer *lexer, int *heredoc_flag);
char		*create_token(t_lexer *lexer, int *heredoc_flag);

int	handle_char(t_lexer *lexer, int *heredoc_flag)
{
	char	*curr_char;

	curr_char = lexer->str + lexer->index;
	if (is_quote(*curr_char))
	{
		if (handle_quotation_marks(lexer, heredoc_flag) == -1)
		{
			ft_lstclear(&lexer->token_lst, free);
			return (-1);
		}
	}
	else if (is_special(*curr_char))
	{
		if (handle_special(lexer, heredoc_flag) == -1)
		{
			ft_lstclear(&lexer->token_lst, free);
			return (-1);
		}
	}
	else
		lexer->index++;
	return (0);
}

static int	handle_special(t_lexer *lexer, int *heredoc_flag)
{
	if (lexer->str + lexer->index - lexer->token_start > 0
		&& add_new_token_lst(lexer) == -1)
		return (-1);
	lexer->token_start = lexer->str + lexer->index;
	if (ft_strncmp(lexer->str + lexer->index, "<<", 2) == 0)
		*heredoc_flag = 1;
	while (is_special(lexer->str[lexer->index]))
		lexer->index++;
	if (add_new_token_lst(lexer) == -1)
		return (-1);
	lexer->token_start = lexer->str + lexer->index;
	return (0);
}

static char	*copy_quoted_text(char *token, t_lexer *lexer)
{
	char	quote;

	quote = lexer->str[lexer->index];
	token = append_text(token, lexer->token_start,
			lexer->index - (lexer->token_start - lexer->str));
	lexer->token_start = lexer->str + ++lexer->index;
	lexer->index = ft_strchr(lexer->token_start, quote) - lexer->str;
	token = append_text(token, lexer->token_start,
			lexer->index - (lexer->token_start - lexer->str));
	lexer->token_start = lexer->str + ++lexer->index;
	return (token);
}

static int	add_new_text_node(t_lexer *lexer, char *token)
{
	t_list	*new_node;

	new_node = ft_lstnew((void *)token);
	if (new_node == NULL)
	{
		free(token);
		return (-1);
	}
	ft_lstadd_back(&lexer->token_lst, new_node);
	return (0);
}

static int	handle_quotation_marks(t_lexer *lexer, int *heredoc_flag)
{
	char	*token;

	token = create_token(lexer, heredoc_flag);
	while (1)
	{
		if (lexer->str[lexer->index] == '\0'
			|| is_special(lexer->str[lexer->index])
			|| is_space(lexer->str[lexer->index]))
		{
			token = append_text(token, lexer->token_start,
					lexer->index - (lexer->token_start - lexer->str));
			lexer->token_start = lexer->str + lexer->index;
			break ;
		}
		else if (is_quote(lexer->str[lexer->index]))
			token = copy_quoted_text(token, lexer);
		else
			lexer->index++;
	}
	if (token == NULL)
		return (-1);
	return (add_new_text_node(lexer, token));
}
