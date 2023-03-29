/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:50:23 by tvillare          #+#    #+#             */
/*   Updated: 2023/03/29 19:55:27 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

static int	find_char(char *str, char c)
{
	int	i;

	i = -1;
	while(str[++i] != '\0')
		if (str[i] == c)
			return (i);
	return (-1);
}

int	find_env(char **env, char *str)
{
	int		i;
	int		len;

	len =  find_char(str, '=');
	if (len == -1 || len == 0)
		return (-1);
	i = -1;
	while (env[++i] != '\0')
		if (ft_strncmp(env[i], str, len) == 0)
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
			//free (env[find]);
			env[find] = ft_strdup(comand[i]);
			mod++;
		}
	}
	return (mod);
}

int	to_future(char **str, int i)
{
	int		base;
	int		len;

	base = i;
	len = find_char(str[base], '=');
	while (str[++i] != '\0')
		if (len == find_char(str[i], '=') && ft_strncmp(str[base], str[i], len) == 0)
			return(i);
	return (-1);
}

int	len_doble(char **str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i] != NULL)
		if (ft_strchr(str[i], '=') != NULL && to_future(str, i) == -1)
			count++;
	return (count);
}

int	len_doble_base(char **str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i] != NULL)
		if (ft_strchr(str[i], '=') != NULL)
			count++;
	return (count);
}
