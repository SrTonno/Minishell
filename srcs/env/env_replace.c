/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:27:34 by tvillare          #+#    #+#             */
/*   Updated: 2023/05/08 13:32:50 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"


//&& (i != 0 && org[i - 1] != '?')
static int	condicion_rep(char *org, int i)
{
	if (org[i] != '$' && org[i] != ' ' && org[i] != '\0'
		&& org[i - 1] != '?' && org[i] != '/' && org[i] != '>'
		&& org[i] != '<' && org[i] != '|')
		return (1);
	return (0);
}

static int	move_letter_rem(char *org, int i)
{
	while (condicion_rep(org, i))
		i++;
	return (i);
}

static int	replace_var(int j, char *dst, char *add)
{
	int	a;

	if (add != NULL)
	{
		a = find_char(add, '=') + 1;
		while (add[a] != '\0')
			dst[j++] = add[a++];
	}
	return (j);
}

char	*replace_env(int len, char *org, char *add)
{
	int		i;
	int		j;
	char	*dst;
	int		mark;

	if (len <= 0)
		return (NULL);
	dst = ft_calloc(len + 1, sizeof(char));
	if (dst == NULL)
		return (NULL);
	mark = find_var(org);
	i = 0;
	j = 0;
	while (len >= j)
	{
		if (i == mark)
		{
			if (org[++i] == '?')
				dst[j++] = '0';
			else
				j = replace_var(j, dst, add);
			i = move_letter_rem(org, i);
		}
		else
			dst[j++] = org[i++];
	}
	return (dst);
}
