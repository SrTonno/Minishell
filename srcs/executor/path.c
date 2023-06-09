/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 18:24:28 by javmarti          #+#    #+#             */
/*   Updated: 2023/04/02 18:24:28 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	**create_paths(char *envp[])
{
	int		index;
	char	**paths;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
			return (get_paths_envp(envp));
		index++;
	}
	paths = (char **)ft_calloc(1, sizeof(char *));
	if (paths == NULL)
		return (NULL);
	paths[0] = ft_strdup("");
	if (paths[0] == NULL)
	{
		free(paths);
		return (NULL);
	}
	return (paths);
}

int	check_binary_path(char *command, char **paths)
{
	char	*binary;
	int		index;

	index = -1;
	while (paths[++index])
	{
		binary = ft_strjoin(paths[index], command);
		if (binary == NULL)
			return (error_msg(MALLOC_ERROR, NULL));
		if (access(binary, X_OK) == 0)
		{
			free(binary);
			return (0);
		}
		if (access(binary, F_OK) == 0 && access(binary, X_OK) == -1)
		{
			free(binary);
			return (error_msg(COMM_NPERM, command));
		}
		free(binary);
	}
	return (error_msg(COMM_NFOUND, command));
}

int	check_binary(char *command, char **paths)
{
	if (is_builtin(command))
		return (0);
	if (*command == '\0')
		return (error_msg(COMM_NFOUND, command));
	if (ft_strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (0);
		if (access(command, F_OK) == -1)
			return (error_msg(NO_FILE_DIR, command));
		if (access(command, X_OK) == -1)
			return (error_msg(COMM_NPERM, command));
		return (error_msg(NO_FILE_DIR, command));
	}
	return (check_binary_path(command, paths));
}

char	*find_binary(char *command, char **paths)
{
	int		index;
	char	*binary;

	if (ft_strchr(command, '/') || is_builtin(command))
		return (ft_strdup(command));
	index = -1;
	while (paths[++index])
	{
		binary = ft_strjoin(paths[index], command);
		if (binary == NULL)
			return (NULL);
		if (access(binary, X_OK) == 0)
			return (binary);
		free(binary);
	}
	return (NULL);
}
