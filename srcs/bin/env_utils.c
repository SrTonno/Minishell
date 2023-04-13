/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:50:23 by tvillare          #+#    #+#             */
/*   Updated: 2023/04/13 17:25:16 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"
#include <limits.h>

int	to_future(char **str, int i)
{
	int		base;
	int		len;

	base = i;
	len = find_char(str[base], '=');
	while (str[++i] != NULL)
		if (len == find_char(str[i], '=')
			&& ft_strncmp(str[base], str[i], len) == 0)
			return (i);
	return (-1);
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

	dst = ft_calloc(len + 1, sizeof(char));
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
			while (org[i] != '$' && org[i] != ' ' && org[i] != '\0'
				&& org[i - 1] != '?')
				i++;
		}
		else
			dst[j++] = org[i++];
	}
	return (dst);
}

int	export_util(char **env, char **comand)
{
	int	mod;
	int	len;

	mod = find_mod_env(env, comand);
	len = len_doble(comand);
	return ((len) - mod);
}
