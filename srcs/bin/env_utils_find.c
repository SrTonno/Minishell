/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_find.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:36:31 by tvillare          #+#    #+#             */
/*   Updated: 2023/04/03 16:32:07 by tvillare         ###   ########.fr       */
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
		if (len == (int)ft_strlen(env[i]) && ft_strncmp(env[i], str, len) == 0) // && (env[i][(len + 1)] == '=')
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
		if ((len > i && str[i] == '$' && quotes == 0)
			&& (str[(i + 1)] != ' ' || str[i + 1] == '?'))
			return (i);
	}
	return (-1);
}
