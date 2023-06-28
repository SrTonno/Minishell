/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:35:50 by tvillare          #+#    #+#             */
/*   Updated: 2023/06/28 15:36:55 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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

	if (g_status == 2)
		return (2);
	status = exec_child(ast, paths, envp);
	if (status == -2)
		return (0);
	return (status);
}
