/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:55:51 by javmarti          #+#    #+#             */
/*   Updated: 2023/05/05 13:26:42 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"
#include "env.h"

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
				printf("-bash: unset: '%s': not a valid identifier\n", str[i]);
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

int	unset_env(char ***env, char **comand)
{
	int		del;
	int		len;
	char	**new_env;

	printf("UNSET\n");
	del = len_error_unset(env[0], comand);
	if (del == 0)
		return (0);
	len = len_doble_base(env[0]);
	new_env = ft_calloc((len - del) + 1, sizeof(char *));
	if (new_env == NULL)
		exit (1);
	delete_unset(new_env, env[0], comand);
	free (env);
	int tmp;
	env[0] = new_env;
	return (0);
}

int	ft_unset(char ***env, char **command)
{
	unset_env(env, command);
	return (0);
}
