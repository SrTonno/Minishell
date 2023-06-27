/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:14:11 by tvillare          #+#    #+#             */
/*   Updated: 2023/06/27 20:36:14 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
mode == 1 No expand heredoc
mode == 0 Expand all
*/
char	*env_expand(char ***env, char *input, int mode)
{
	int		len;
	int		top;
	char	*var;
	char	*str;
	int		i;

	len = find_var(input, mode) + 1;
	top = find_var_end(input, len);
	var = ex_calloc((top - len) + 1, sizeof(char));
	ft_strlcpy(var, input + len, (top - len));
	i = find_env_basic(env[0], var);
	if (var[0] == '?')
		str = replace_env((ft_strlen(input) - 1) + \
			len_num(g_status), input, "?", mode);
	else if (input[len] == DOUBLE_QUOTE || input[len] == SINGLE_QUOTE)
		str = replace_env((ft_strlen(input) - \
			1), input, NULL, mode);
	else if (i >= 0 && ft_strlen(env[0][i]) - 1 > find_char(env[0][i], '='))
		str = replace_env((ft_strlen(input) + ft_strlen(env[0][i])) \
			- ((ft_strlen(var) + 1) * 2), input, env[0][i], mode);
	else
		str = replace_env((ft_strlen(input) - \
			(ft_strlen(var) + 1)), input, NULL, mode);
	(free (var), free (input));
	return (str);
}

char	**void_env(void)
{
	char	**new_env;
	char	*a;

	new_env = ft_calloc(4 + 1, sizeof(char *));
	if (new_env == NULL)
		exit (1);
	a = getcwd(NULL, 0);
	if (a != NULL)
	{
		new_env[0] = ft_strjoin("PWD=", a);
		free (a);
	}
	else
		new_env[0] = ft_strdup("PWD=/");
	new_env[1] = ft_strdup("SHLVL=1");
	new_env[2] = ft_strdup("_=/usr/bin/env");
	return (new_env);
}

char	**malloc_env(char **env)
{
	int		i;
	int		len;
	char	**new_env;

	len = len_doble_base(env);
	if (len == 0)
		return (void_env());
	new_env = ft_calloc(len + 1, sizeof(char *));
	if (new_env == NULL)
		(free(new_env), exit (1));
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			new_env[i] = check_shlvl(env[i]);
		else
			new_env[i] = ft_strdup(env[i]);
		if (new_env[i] == NULL)
			(free_split(new_env), exit (1));
	}
	return (new_env);
}
