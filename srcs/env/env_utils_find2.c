/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_find2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:32:08 by tvillare          #+#    #+#             */
/*   Updated: 2023/06/27 15:57:47 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdio.h>

static void	type_quotes(int *doble, int *simple, char chr, int mode)
{
	if (chr == SINGLE_QUOTE && mode == 1)
	{
		if (*simple == 0 && *doble == 0)
			*simple = 1;
		else if (*simple == 1)
			*simple = 0;
	}
	else if (chr == DOUBLE_QUOTE && mode == 1)
	{
		if (*doble == 0 && *simple == 0)
			*doble = 1;
		else if (*doble == 1)
			*doble = 0;
	}
}

int	is_heredoc(int heredoc, char *str, int i, int len)
{
	if (len > i && str[i] == '<' && str[i + 1] == '<')
		return (1);
	else if (len > i && ft_isalpha(str[i]) == 1)
		return (0);
	return (heredoc);
}

void	set_var(int *heredoc, int *i, int *simple, int *doble)
{
	*heredoc = 0;
	*i = -1;
	*simple = 0;
	*doble = 0;
}

int	find_var(char *str, int mode)
{
	int	i;
	int	len;
	int	simple;
	int	doble;
	int	heredoc;

	set_var(&heredoc, &i, &simple, &doble);
	len = ft_strlen(str);
	while (str[++i] != '\0')
	{
		type_quotes(&doble, &simple, str[i], mode);
		if ((len > i && str[i] == '$' && simple == 0
				&& str[i + 1] != '\0' && str[i + 1] != '\n'
				&& str[i + 1] != '$' && heredoc == 0)
			&& (str[(i + 1)] != ' ' || str[i + 1] == '?')
			&& (doble == 0 || (doble == 1 && (str[(i + 1)] != SINGLE_QUOTE
						&& str[(i + 1)] != DOUBLE_QUOTE)))
			&& (mode == 1 || (mode == 0 && str[i + 1] != DOUBLE_QUOTE
					&& str[(i + 1)] != DOUBLE_QUOTE)))
			return (i);
		if (mode == 1 && (doble == 0 || (doble == 1 && heredoc == 1)) && \
			(simple == 0 || (simple == 1 && heredoc == 1)))
			heredoc = is_heredoc(heredoc, str, i, len);
	}
	return (-1);
}

int	find_var_end(char *str, int i)
{
	while (str[i] != '$' && str[i] != ' '
		&& str[i - 1] != '?' && str[i] != '\0'
		&& str[i] != '/' && str[i] != '>'
		&& str[i] != '<' && str[i] != '|' && str[i] != '\n'
		&& str[i] != DOUBLE_QUOTE && str[i] != SINGLE_QUOTE)
		i++;
	i++;
	return (i);
}
