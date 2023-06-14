/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_find2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:32:08 by tvillare          #+#    #+#             */
/*   Updated: 2023/06/14 14:41:43 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdio.h>

void	type_quotes(int *doble, int *simple, char chr)
{
	if (chr == SINGLE_QUOTE)
	{
		//printf("simple -> %d, doble %d", *simple, *doble);
		if (*simple == 0 && *doble == 0)
			*simple = 1;
		else if (*simple == 1)
			*simple = 0;

	}
	else if (chr == DOUBLE_QUOTE)
	{
		if (*doble == 0 && *simple == 0)
			*doble = 1;
		else if (*doble == 1)
			*doble = 0;
	}
}
int	find_var(char *str)
{
	int	i;
	int	len;
	int	simple;
	int	doble;

	i = -1;
	simple = 0;
	doble = 0;
	len = ft_strlen(str);
	while (str[++i] != '\0')
	{
		type_quotes(&doble, &simple, str[i]);
		if ((len > i && str[i] == '$' && simple == 0 && str[i + 1] != '\0'
				&& str[i + 1] != '$')
			&& (str[(i + 1)] != ' ' || str[i + 1] == '?'))
			return (i);
	}
	return (-1);
}

int	find_var_end(char *str, int i)
{
	while (str[i] != '$' && str[i] != ' '
		&& str[i - 1] != '?' && str[i] != '\0'
		&& str[i] != '/' && str[i] != '>'
		&& str[i] != '<' && str[i] != '|'
		&& str[i] != DOUBLE_QUOTE && str[i] != SINGLE_QUOTE)
		i++;
	i++;
	return (i);
}
