/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:27:34 by tvillare          #+#    #+#             */
/*   Updated: 2023/06/17 18:07:07 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	condicion_rep(char *org, int i)
{
	if (org[i] != '$' && org[i] != ' ' && org[i] != '\0'
		&& org[i - 1] != '?' && org[i] != '/' && org[i] != '>'
		&& org[i] != '<' && org[i] != '|'
		&& org[i] != DOUBLE_QUOTE && org[i] != SINGLE_QUOTE)
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

static char	*fuck_norminete(int *i, int *j, int len)
{
	char	*dst;

	*i = 0;
	*j = 0;
	dst = ex_calloc(len + 1, sizeof(char));
	return (dst);
}

char	*replace_env(int len, char *org, char *add, int mode)
{
	int		i;
	int		j;
	char	*dst;
	int		mark;

	if (len <= 0)
		return (NULL);
	dst = fuck_norminete(&i, &j, len);
	mark = find_var(org, mode);
	while (len >= j)
	{
		if (i == mark)
		{
			if (org[++i] == '?')
				j = copy_num(g_status, dst, j);
			else if (org[i] == DOUBLE_QUOTE || org[i] == SINGLE_QUOTE)
				continue ;
			else
				j = replace_var(j, dst, add);
			i = move_letter_rem(org, i);
		}
		else
			dst[j++] = org[i++];
	}
	return (dst);
}
