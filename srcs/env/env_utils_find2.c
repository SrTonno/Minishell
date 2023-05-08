/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_find2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:32:08 by tvillare          #+#    #+#             */
/*   Updated: 2023/05/08 13:50:13 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	find_var(char *str)
{
	int	i;
	int	len;
	int	quotes;

	i = -1;
	quotes = 0;
	len = ft_strlen(str);
	while (str[++i] != '\0')
	{
		if (str[i] == SINGLE_QUOTE)
		{
			if (quotes == 0)
				quotes = 1;
			else
				quotes = 0;
		}
		if ((len > i && str[i] == '$' && quotes == 0 && str[i + 1] != '\0'
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
		&& str[i] != '<' && str[i] != '|')
		i++;
	i++;
	return (i);
}
