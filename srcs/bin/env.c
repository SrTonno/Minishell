/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:14:11 by tvillare          #+#    #+#             */
/*   Updated: 2023/03/29 19:46:18 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

/*
-------Basic-------
0.-Comprobar formato
1.- buscar si existe la variable, si existe cambiar contenido y si no...
2.-crear malloc(char *) de la suma de len de env y comados
3.-Asignar
*/


//Find busca y modifica en caso de cuencidencia y debiulve un char ** de las variables NO encontradas

//comparar que no te pasen el mismo 2 veces(coger el ultimo)
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
	//while (len_com > ++j)
	while (comand[++j] != '\0')
	{
		if (ft_strchr(comand[j], '=') != NULL && find_env(env, comand[j]) <= 0  && to_future(comand, j) == -1)
			str[i++] = ft_strdup(comand[j]);
	}
	//free(env);
	//tmp
	int tmp;
	tmp = 0;
	while (comand[tmp] != '\0')
		free(comand[tmp++]);
	free(comand);
	printf("----------------------------\n");
	return(str);
}
/*
char	**unset(char **env, char **comand)
{
	int		len_env;
	int		len_com;
	char	**str;

}
*/
