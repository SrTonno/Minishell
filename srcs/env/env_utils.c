/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:50:23 by tvillare          #+#    #+#             */
/*   Updated: 2023/05/06 19:29:22 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <limits.h>
#include <stdio.h>

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

int	export_util(char **env, char **comand)
{
	int	mod;
	int	len;

	mod = find_mod_env(env, comand);
	len = len_doble(comand);
	return ((len) - mod);
}
