/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 13:17:45 by tvillare          #+#    #+#             */
/*   Updated: 2023/04/09 18:31:36 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"
#include "libft.h"

#include <stdio.h>
#include <stdlib.h>

static int	len_error_unset(char **env, char **str)
{
	int	i;
	int	count;
	int	error;

	error = 0;
	count = 0;
	i = 0;
	while (str[++i] != NULL)
	{
		if ((ft_isalpha(str[i][0]) == 0 && str[i][0] != '_')
			|| find_char(str[i], '=') >= 0)
		{
			if (error == 0)
				printf("unset: %s: invalid parameter name\n", str[i]);
			error++;
		}
		else if (find_env_basic(env, str[i]) >= 0 && to_future(str, i) == -1)
			count++;
	}
	return (count);
}

static void	delete_unset(char **new_env, char **env, char **comand)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		if (find_env_len(comand, env[i]) == -2)
			new_env[j++] = env[i++];
		else
			free (env[i++]);
	}
}

char	**unset_env(char **env, char **comand)
{
	int		del;
	int		len;
	char	**new_env;

	printf("UNSET\n");
	del = len_error_unset(env, comand);
	if (del == 0)
		return (env);
	len = len_doble_base(env);
	new_env = ft_calloc((len - del) + 1, sizeof(char *));
	delete_unset(new_env, env, comand);
	free (env);
	return (new_env);
}
/*
	int tmp;
	tmp = 0;
	while (comand[tmp] != NULL)
		free(comand[tmp++]);
	free(comand);
*/
