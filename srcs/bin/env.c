/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:14:11 by tvillare          #+#    #+#             */
/*   Updated: 2023/04/08 15:44:33 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		printf("%s\n", env[i++]);
	printf("--------------------\n");
}

char	*env_expand(char **env, char *input)
{
	int		len;
	int		top;
	char	*var;
	char	*str;
	int		i;

	len = find_var(input) + 1;
	top = find_var_end(input, len);
	var = ft_calloc((top - len) + 1, sizeof(char));
	ft_strlcpy(var, input + len, (top - len));
	i = find_env_basic(env, var);
	if (var[0] == '?')
		str = replace_env(ft_strlen(input) - 1, input, "?");
	else if (i >= 0)
		str = replace_env((ft_strlen(input) + ft_strlen(env[i])) \
			- ((ft_strlen(var) + 1) * 2), input, env[i]);
	else
		str = replace_env((ft_strlen(input) - \
			(ft_strlen(var) + 1)), input, NULL);
	free (var);
	free (input);
	return (str);
}

//Error se sale porque no encuentra NULL// puede duplicar datos
char	**ft_export(char **env, char **comand)
{
	int		i;
	int		j;
	int		len_env;
	int		len_com;
	char	**str;

	i = 0;
	printf("Export\n");
	len_env = len_doble_base(env);
	printf("len_env->%d\n", len_env);
	//if (len_env != 0)
		len_com = export_util(env, comand);
	//else
		//len_com = len_doble(comand);
	printf("len_com%d\n", len_com);
	if (len_com <= 0)
	{
		printf("////////////////////////IGUALLLLLLLLLLLL\n");
		return (env);
	}
	str = ft_calloc((len_com + len_env + 1), sizeof(char *));
	j = 0;
	while (len_env != 0 && len_env > j)
		str[i++] = env[j++];
	j = 0;
	while (comand[++j] != '\0')
		if (find_char(comand[j], '=') > 0 && find_env(env, comand[j]) <= 0
			&& to_future(comand, j) == -1)
			str[i++] = ft_strdup(comand[j]);
	printf("%d/%d\n", i, ((len_com + len_env + 1)));
	str[i] = NULL;
	//free (env);
	printf("FINN Export\n");
	//tmp
	int tmp;
	tmp = 0;
	while (comand[tmp] != NULL)
		free(comand[tmp++]);
	free(comand);
	printf("FINN Export 2\n");
	return (str);
}
/*
	//tmp
	int tmp;
	tmp = 0;
	while (comand[tmp] != '\0')
		free(comand[tmp++]);
	free(comand);
	printf("----------------------------\n");
*/

char	**malloc_env(char **env)
{
	int		i;
	int		len;
	char	**new_env;

	len = len_doble_base(env);
	printf("MAALLOC\n");
	new_env = ft_calloc(len + 1, sizeof(char *));
	i = -1;
	while (env[++i] != '\0')
		new_env[i] = ft_strdup(env[i]);
	env[++i] = NULL;
	return (new_env);
}

//Peta cuando se elimina la ultima variable
char	**ft_unset(char **env, char **comand)
{
	int		len_env;
	int		len_com;
	char	**str;
	int		i;
	int		j;

	printf("UNSET");
	len_com = len_doble_uniq_one(comand, env, 0);
	if (len_com < 0)
	{
		printf("unset: %s: invalid parameter name\n", comand[(len_com * -1)]);
		len_com = len_doble_uniq_one(comand, env, 1);
	}
	printf("%d\n", len_com);
	len_env = len_doble_base(env);
	str = ft_calloc((len_env - len_com) + 1, sizeof(char *));
	str[((len_env - len_com) + 1)] = NULL;
	i = -1;
	j = 0;
	printf("NEW_ENV\n");
	//while (len_env > ++i)
	while (env[++i] != NULL)
	{
		//printf("(%d)->>%s)\n", i, env[i]);
		if (find_env_len(comand, env[i]) == -2)
		{
			//printf("(%d)\n", i);
			str[j++] = env[i];
		}
		else
		{
			printf("///(%d)->>%s\n)", i, env[i]);
			//free(env[i]);
			//env[i] = NULL;
		}
	}
	printf("\n%d/%d\n", j, (((len_env - len_com) + 1)));
	str[j] = NULL;
	//if (env != NULL)
	//free(env);
	printf("FINN UNSET\n");
	//tmp
	/*int tmp;
	tmp = 0;
	while (comand[tmp] != NULL)
		free(comand[tmp++]);
	free(comand);*/
	printf("FINN FIN UNSET\n");
	return (str);
}
