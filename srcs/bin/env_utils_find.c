/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_find.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:36:31 by tvillare          #+#    #+#             */
/*   Updated: 2023/04/14 18:24:20 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

int	find_char(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		if (str[i] == c)
			return (i);
	return (-1);
}

int	find_env_basic(char **env, char *str)
{
	int		i;
	int		len;

	len = ft_strlen(str);
	i = -1;
	while (env[++i] != '\0')
		if (len == find_char(env[i], '=') && ft_strncmp(env[i], str, len) == 0)
			return (i);
	return (-2);
}

int	find_env(char **env, char *str)
{
	int		i;
	int		len;

	len = find_char(str, '=');
	if (len == -1 || len == 0)
		return (-1);
	i = -1;
	while (env[++i] != '\0')
		if (len == find_char(env[i], '=') && ft_strncmp(env[i], str, len) == 0)
			return (i);
	return (-2);
}

int	find_env_len(char **env, char *str)
{
	int		i;
	int		len;

	len = find_char(str, '=');
	if (len == -1 || len == 0)
		return (-1);
	i = 0;
	while (env[++i] != '\0')
		if (len == (int)ft_strlen(env[i]) && ft_strncmp(env[i], str, len) == 0)
			return (i);
	return (-2);
}

int	find_mod_env(char **env, char **comand)
{
	int	i;
	int	find;
	int	mod;

	mod = 0;
	i = 0;
	while (comand[++i] != '\0')
	{
		find = find_env(env, comand[i]);
		if (find >= 0)
		{
			free (env[find]);
			env[find] = ft_strdup(comand[i]);
			mod++;
		}
	}
	return (mod);
}
