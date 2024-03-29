/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:59:37 by javmarti          #+#    #+#             */
/*   Updated: 2023/06/27 15:55:23 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"
#include "env.h"

static int	len_error_expot(char **str, int *code)
{
	int	i;
	int	count;
	int	error;

	error = 0;
	count = 1;
	i = -1;
	while (str[++i] != NULL)
	{
		if ((ft_isalpha(str[i][0]) == 0 && str[i][0] != '_'))
		{
			if (error == 0)
			{
				printf("export: not an identifier:%s\n", str[i]);
				*code = 1;
			}
			error++;
		}
		else if (find_char(str[i], '=') > 0 && to_future(str, i) == -1)
			count++;
	}
	return (count);
}

static int	len_comando(char **coman, char **env, int *error)
{
	int	len;
	int	mod;

	mod = find_mod_env(env, coman);
	len = len_error_expot(coman, error);
	return (len - mod);
}

void	crearte_new_env(char **dst, char **comd, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] != NULL)
		dst[j++] = env[i++];
	i = -1;
	while (comd[++i] != NULL)
	{
		if ((ft_isalpha(comd[i][0]) == 1 || comd[i][0] == '_')
			&& find_char(comd[i], '=') > 0
			&& to_future(comd, i) == -1 && find_env(env, comd[i]) == -2)
			dst[j++] = ft_strdup(comd[i]);
	}
	dst[j] = NULL;
}

int	ft_export(char ***env, char **coman)
{
	char	**new_env;
	int		len_com;
	int		len_env;
	int		error;

	error = 0;
	if (len_doble_base(coman) == 1)
		print_export(env[0]);
	len_com = len_comando(coman, env[0], &error);
	if (len_com <= 1)
		return (error);
	len_env = len_doble_base(env[0]);
	new_env = ex_calloc((len_com + len_env + 1), sizeof(char *));
	crearte_new_env(new_env, coman, env[0]);
	free(env[0]);
	env[0] = new_env;
	return (error);
}
