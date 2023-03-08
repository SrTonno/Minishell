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

int	handle_dollar(t_lexer *lexer)
{
	if (add_new_token_lst(lexer) == -1)
		return (-1);
	lexer->token_start = lexer->str + lexer->index;
	while (is_env_var_char(lexer->str[++lexer->index]))
		;
	if (add_new_token_lst(lexer) == -1)
		return (-1);
	lexer->token_start = lexer->str + lexer->index;
	return (0);
}

t_list	*tokenize(char *_lexer)
{
	t_lexer	lexer;

	lexer = init_lexer(_lexer);
	while (lexer.str[lexer.index] != '\0')
	{
		while (is_space(lexer.str[lexer.index]))
			lexer.index++;
		lexer.token_start = lexer.str + lexer.index;
		while (is_space(lexer.str[lexer.index]) == 0)
		{
			if (lexer.str[lexer.index] == SINGLE_QUOTE
				|| lexer.str[lexer.index] == DOUBLE_QUOTE)
			{
				if (handle_quotation_marks(&lexer) == -1)
					return (NULL);
			}
			else if (is_special(lexer.str[lexer.index]))
			{
				if (handle_special(&lexer) == -1)
					return (NULL);
			}
			else if(lexer.str[lexer.index] == '$')
			{
				if (handle_dollar(&lexer) == -1)
					return (NULL);
			}
			else
				lexer.index++;
		}
		if (add_new_token_lst(&lexer) == -1)
			return (NULL);
	}
	return (lexer.token_lst);
}

int	handle_special(t_lexer *lexer)
{
	if (add_new_token_lst(lexer) == -1)
		return (-1);
	lexer->token_start = lexer->str + lexer->index;
	while (is_special(lexer->str[lexer->index]))
		lexer->index++;
	if (add_new_token_lst(lexer) == -1)
		return (-1);
	lexer->token_start = lexer->str + lexer->index;
	return (0);
}

int	handle_env_var(t_lexer *lexer)
{
	char	*curr_pos;
	char	*quotes_end;
	char	*env_var_start;

	curr_pos = lexer->str + lexer->index;
	env_var_start = ft_strchr(curr_pos, '$');
	quotes_end = ft_strchr(curr_pos + 1, *curr_pos);
	while (env_var_start != NULL && env_var_start < quotes_end)
	{
		if (is_space(*(env_var_start + 1)) == 0
			&& *(env_var_start + 1) != DOUBLE_QUOTE)
		{
			lexer->index = (size_t)(env_var_start - lexer->str);
			if (add_new_token_lst(lexer) == -1)
				return (-1);
			lexer->token_start = env_var_start;
			while (is_space(lexer->str[lexer->index]) == 0)
				lexer->index++;
			if (add_new_token_lst(lexer) == -1)
				return (-1);
			lexer->token_start = lexer->str + lexer->index;
		}
		env_var_start = ft_strchr(env_var_start + 1, '$');
	}
	lexer->index = quotes_end - lexer->str + 1;
	if (add_new_token_lst(lexer) == -1)
		return (-1);
	lexer->token_start = quotes_end + 1;
	return (0);
}

int	handle_quotation_marks(t_lexer *lexer)
{
	char	*end_quote;
	char	quote;

	quote = lexer->str[lexer->index];
	end_quote = ft_strchr(lexer->str + lexer->index + 1, quote);
	if (end_quote == NULL)
		lexer->index++;
	else
	{
		if (add_new_token_lst(lexer) == -1)
			return (-1);
		lexer->token_start = lexer->str + lexer->index;
		if (quote == DOUBLE_QUOTE && any_env_var_str(lexer->str + lexer->index))
		{
			if (handle_env_var(lexer) == -1)
				return (-1);
		}
		else
		{
			lexer->index = end_quote - lexer->str + 1;
			if (add_new_token_lst(lexer) == -1)
				return (-1);
			lexer->token_start = lexer->str + lexer->index;
		}
	}
	return (0);
}
