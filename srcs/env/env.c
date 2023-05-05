/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:14:11 by tvillare          #+#    #+#             */
/*   Updated: 2023/05/05 13:04:08 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*env_expand(char ***env, char *input)
{
	int		len;
	int		top;
	char	*var;
	char	*str;
	int		i;

	len = find_var(input) + 1;
	top = find_var_end(input, len);
	var = ft_calloc((top - len) + 1, sizeof(char));
	if (var == NULL)
		exit (0);
	ft_strlcpy(var, input + len, (top - len));
	i = find_env_basic(env[0], var);
	if (var[0] == '?')
		str = replace_env(ft_strlen(input) - 1, input, "?");
	else if (i >= 0)
		str = replace_env((ft_strlen(input) + ft_strlen(env[0][i])) \
			- ((ft_strlen(var) + 1) * 2), input, env[0][i]);
	else
		str = replace_env((ft_strlen(input) - \
			(ft_strlen(var) + 1)), input, NULL);
	free (var);
	free (input);
	if (str == NULL)
		return (NULL);
	return (str);
}

char	***malloc_env(char **env)
{
	int		i;
	int		len;
	char	***new_env;

	new_env = ft_calloc(1, sizeof(char *));
	//proteger malloc
	len = len_doble_base(env);
	new_env[0] = ft_calloc(len + 1, sizeof(char *));
	i = -1;
	while (env[++i] != '\0')
		new_env[0][i] = ft_strdup(env[i]);
	new_env[0][++i] = NULL;
	return (new_env);
}
