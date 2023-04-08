/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:38:31 by tvillare          #+#    #+#             */
/*   Updated: 2023/04/08 19:29:41 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"
#include "libft.h"

#include <stdio.h>
#include <stdlib.h>

//refactorial export and undet
/*
EXPOT PASOS:
0.-Controbar que las variaables no enpeiezan por caracteres que no sean letras o '_'
1.-Comprobar si hay variables validas que existan en env y en tal caso sustituirlas
2.-En caso que despues del paso 1 no quedan variables validas debolber finalizar y debolver env
3.-En caso contrario de 2, obtener la cantidad de variables validas = (len de env + (len de variables validas del comando - modificaciones del env))
4.-mallocquerar el char**
5.-Pasar env a new_env
5.-Pasar las variables validas del input al new_env
EXTTRAAA(CAOSOS con los que tener cuidado)
->si env esya bacio (env -i ./minishell)
->UNA variable valida es una que tenga '='; el primer caracter SOLO puede ser letras o '_' ; no exista esa variable posterior en la instruccion
->Intentar siempre reasignar memoria
*/

static int len_error_expot(char **str)//revisar funcion
{
	int	i;
	int	count;
	int	error;

	error = 0;
	count = 1;
	i = -1;
	while (str[++i] != NULL)
	{
		if ((ft_isalpha(str[i][0]) == 0 && str[i][0] != '_'))//rebisar
		{
			if (error == 0)
				printf("export: not an identifier:%s\n", str[i]);
			error++;
		}
		else if(find_char(str[i], '=') > 0 && to_future(str, i) == -1)
			count++;
	}
	return (count);
}

static int	len_comando(char **coman, char **env)
{
	int	len;
	int	mod;

	mod = find_mod_env(env, coman); //reutilizado
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
	while (comd[++i] != NULL)
	{
		if ((ft_isalpha(comd[i][0]) == 1 || comd[i][0] == '_') && find_char(env[i], '=') > 0
			&& to_future(comd, i) == -1 && find_env(env, comd[i]) == -2)
			dst[j++] = ft_strdup(comd[i]);
	}
	dst[j] = NULL;
}

char	**export_env(char **env, char **coman)
{
	char	**new_env;
	int		len_com;
	int		len_env;

	len_com = len_comando(coman, env);
	printf("%d\n", len_com);
	if (len_com <= 0)
		return (env);
	printf("--------------------\n");
	len_env = len_doble_base(env);
	printf("%d + %d\n", len_com, len_env);
	new_env = ft_calloc((len_com + len_env + 1), sizeof(char *));
	crearte_new_env(new_env, coman, env);
	return (new_env);
}

/*
UNSET PASSOS:
1.-Comprobar Si hay alguna variable que contenga '=', si la hay mostrar mensage de error y continual con la ejecuion
2.-Conttar cuantas valiables de la instrucion existen en env
3.-mallocquerar el char**
4.-Pasar las variables validas del input y que exitan en env al new_env y las que no liberarlas
4.-
5.-
EXTTRAAA(CAOSOS con los que tener cuidado)
->
->
->
*/
