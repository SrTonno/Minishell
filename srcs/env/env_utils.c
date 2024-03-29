/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:50:23 by tvillare          #+#    #+#             */
/*   Updated: 2023/06/24 18:56:35 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <limits.h>
#include <stdio.h>

int	to_future(char **str, int i)
{
	int		base;
	size_t	len;

	base = i;
	len = find_char(str[base], '=');
	while (str[++i] != NULL)
		if (len == find_char(str[i], '=')
			&& ft_strncmp(str[base], str[i], len) == 0)
			return (i);
	return (-1);
}

int	export_util(char **env, char **comand)
{
	int	mod;
	int	len;

	mod = find_mod_env(env, comand);
	len = len_doble(comand);
	return ((len) - mod);
}

int	len_num(int num)
{
	int	i;

	i = 0;
	while (num)
	{
		i++;
		num = num / 10;
	}
	return (i);
}

int	copy_num(int status, char *dst, int j)
{
	char	*num;
	int		i;

	i = 0;
	num = ft_itoa(status);
	while (num[i] != '\0')
		dst[j++] = num[i++];
	free(num);
	return (j);
}
