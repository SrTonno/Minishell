/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 13:17:45 by tvillare          #+#    #+#             */
/*   Updated: 2023/04/09 17:30:57 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"
#include "libft.h"

#include <stdio.h>
#include <stdlib.h>

/*
UNSET PASSOS:
1.-Comprobar Si hay alguna variable que contenga '=', si la hay mostrar mensage de error y continual con la ejecuion
2.-Conttar cuantas valiables de la instrucion existen en env
3.-mallocquerar el char**
4.-Pasar las variables validas del input y que exitan en env al new_env y las que no liberarlas
EXTTRAAA(CAOSOS con los que tener cuidado)
->
*/

static int len_error_unset(char **env, char **str)//revisar funcion
{
	int	i;
	int	count;
	int	error;

	error = 0;
	count = 0;
	i = 0;
	while (str[++i] != NULL)
	{
		if ((ft_isalpha(str[i][0]) == 0 && str[i][0] != '_') || find_char(str[i], '=') >= 0)//rebisar
		{
			if (error == 0)
				printf("unset: %s: invalid parameter name\n", str[i]);
			error++;
		}
		else if(find_env_basic(env, str[i]) >= 0 && to_future(str, i) == -1)
		{
			printf("%d->%s\n", count, str[i]);
			count++;
		}
	}
	return (count);
}

//static char	**delete_unset()

char	**unset_env(char **env, char **comand)
{
	int		del;
	int		len;
	int		i;
	int		j;
	char	**new_env;

	printf("UNSET\n");
	del = len_error_unset(env, comand);
	if (del == 0)
		return (env);
	len = len_doble_base(env);
	new_env = ft_calloc((len - del) + 1, sizeof(char *));
	i = 0;
	j = 0;
	printf("-------------------------\n");
	while(env[i] != NULL)
	{
		//printf("ª%s -> %d\n", env[i], find_env_len(comand, env[i]));
		if(find_env_len(comand, env[i]) == -2)
			new_env[j++] = env[i++];
		else
		{
			printf("->%s\n", env[i]);
			free(env[i++]);
		}
	}
	printf("FIN UNSET\n");
	free(env);
	return (new_env);
}
