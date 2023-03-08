/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:58:06 by javmarti          #+#    #+#             */
/*   Updated: 2023/03/08 12:58:06 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	init_lexer(char *_lexer)
{
	t_lexer	lexer;

	lexer.str = _lexer;
	lexer.len = ft_strlen(lexer.str);
	lexer.index = 0;
	lexer.token_lst = NULL;
	lexer.token_len = 0;
	return (lexer);
}

int	any_env_var_str(char *str)
{
	char	*env_var_start;
	char	*quotes_end;

	env_var_start = ft_strchr(str, '$');
	quotes_end = ft_strchr(str + 1, *str);
	while (env_var_start != NULL && env_var_start < quotes_end)
	{
		if (is_space(*(env_var_start + 1)) == 0)
			return (1);
		env_var_start = ft_strchr(env_var_start + 1, '$');
	}
	return (0);
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
