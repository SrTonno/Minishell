/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:59:37 by javmarti          #+#    #+#             */
/*   Updated: 2023/04/28 17:59:38 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

static int	len_error_expot(char **str)
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
				printf("export: not an identifier:%s\n", str[i]);
			error++;
		}
		else if (find_char(str[i], '=') > 0 && to_future(str, i) == -1)
		{
			printf("%d->%s\n", count, str[i]);
			count++;
		}
	}
	return (count);
}

static int	len_comando(char **coman, char **env)
{
	int	len;
	int	mod;

	mod = find_mod_env(env, coman);
	len = len_error_expot(coman);
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
	printf("%ddcrearte_new_env\n", j);
	while (comd[++i] != NULL)
	{

		if ((ft_isalpha(comd[i][0]) == 1 || comd[i][0] == '_')
			&& find_char(comd[i], '=') > 0
			&& to_future(comd, i) == -1 && find_env(env, comd[i]) == -2)
		{
			printf("%s\n", comd[i]);
			dst[j++] = ft_strdup(comd[i]);
		}
	}
	dst[j] = NULL;
}

static void	only_coman(char **dst, char **comd)
{
	int	i;
	int	j;
	int	len_env;
	j = 0;
	i = -1;
	printf("only_coman\n");
	while (comd[++i] != NULL)
	{
		if ((ft_isalpha(comd[i][0]) == 1 || comd[i][0] == '_')
			&& to_future(comd, i) == -1)
			dst[j++] = ft_strdup(comd[i]);
	}
	dst[j] = NULL;
}
char	**export_env(char **env, char **coman)
{
	char	**new_env;
	int		len_com;
	int		len_env;

	printf("EXPORT\n");
	len_com = len_comando(coman, env);
	printf("%d\n", len_com);
	if (len_com <= 1)
		return (env);
	len_env = len_doble_base(env);
	printf("%d + %d\n", len_com, len_env);
	new_env = ft_calloc((len_com + len_env + 1), sizeof(char *));
	if (new_env == NULL)
	{
		//liberar cosas
		exit(1);
	}
	if (len_env == 0)
		only_coman(new_env, coman);
	else
		crearte_new_env(new_env, coman, env);
	free(env);
	int tmp;
	tmp = 0;
	while (coman[tmp] != NULL)
		free(coman[tmp++]);
	free(coman);

	return (new_env);
}

/*
int tmp;
	tmp = 0;
	while (coman[tmp] != NULL)
		free(coman[tmp++]);
	free(coman);
	return (new_env);
*/
