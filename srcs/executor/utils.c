/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:35:50 by tvillare          #+#    #+#             */
/*   Updated: 2023/06/28 19:19:59 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "env.h"

char	*env_expand(char ***env, char *input, int mode);

char	*expand_heredoc(char *input, char ***env, int flag)
{
	while (find_var(input, 0) >= 0 && flag == 1)
	{
		input = env_expand(env, input, 0);
		if (input == NULL)
			return (NULL);
	}
	return (input);
}

int	code_status(t_list *ast, char **paths, char ***envp)
{
	int	status;

	status = exec_child(ast, paths, envp);
	if (g_status == 2)
	{
		write(1, "\n", 1);
		return (-3);
	}
	if (status == -2)
		return (0);
	return (status);
}

int	check_str(char *s1, char *s2)
{
	size_t	index;

	index = 0;
	while (s1[index] || s2[index])
	{
		if (s1[index] == '\0' && s2[index] == '\n')
			return (0);
		if ((unsigned char)s1[index] != (unsigned char)s2[index])
			return ((unsigned char)s1[index] - (unsigned char)s2[index]);
		index++;
	}
	return (0);
}
