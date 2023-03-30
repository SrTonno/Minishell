/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:14:11 by tvillare          #+#    #+#             */
/*   Updated: 2023/03/30 15:25:38 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != '\0')
		printf("%s\n", env[i++]);
}
char	**ft_export(char **env, char **comand)
{
	int		i;
	int		j;
	int		mod;
	int		len_env;
	int		len_com;
	char	**str;

	i = 0;
	mod = find_mod_env(env, comand);
	len_env = len_doble_base(env);
	len_com = len_doble(comand);
	printf("mod->%d; env->%d; comand->%d\n", mod, len_env, len_com);
	if((len_com) < 0)
		return (env);
	str = ft_calloc(((len_com) + len_env + 1), sizeof(char *));
	j = 0;
	while (len_env > j)
		str[i++] = env[j++];
	j = 0;
	while (comand[++j] != '\0')
	{
		if (ft_strchr(comand[j], '=') != NULL && find_env(env, comand[j]) <= 0  && to_future(comand, j) == -1)
			str[i++] = ft_strdup(comand[j]);
	}
	free(env);
	//tmp
	int tmp;
	tmp = 0;
	while (comand[tmp] != '\0')
		free(comand[tmp++]);
	free(comand);
	printf("----------------------------\n");
	return(str);
}

char	**malloc_env(char **env)
{
	int		i;
	int		len;
	char	**new_env;

	len = len_doble_base(env);
	new_env = ft_calloc(len + 1, sizeof(char *));
	i = -1;
	while (env[++i] != '\0')
		new_env[i] = ft_strdup(env[i]);
	return (new_env);

}

char	**ft_unset(char **env, char **comand)
{
	int		len_env;
	int		len_com;
	char	**str;
	int		i;
	int		j;

	len_com = len_doble_uniq_one(comand, env);
	if (len_com < 0)
	{
		printf("unset: %s: invalid parameter name\n", comand[(len_com * -1)]);
		return(env);
	}
	len_env = len_doble_base(env);
	str = ft_calloc((len_env - len_com) + 1, sizeof(char *));
	i = -1;
	j = 0;
	while (len_env > ++i)
	{
		if (find_env(comand, env[i]) == -2)
			str[j++] = env[i];
		else
			free(env[i]);
	}
	free(env);
	//tmp
	int tmp;
	tmp = 0;
	while (comand[tmp] != '\0')
		free(comand[tmp++]);
	free(comand);
	return (str);
}
