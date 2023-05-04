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

char	*get_path_envp(char *envp[])
{
	int		index;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
			return (ft_strchr(envp[index], '=') + 1);
		index++;
	}
	return (NULL);
}

char	**get_paths_envp(char *envp[])
{
	char	**path_splitted;
	int		index;
	char	*aux;

	path_splitted = ft_split(get_path_envp(envp), ':');
	if (path_splitted == NULL)
		return (NULL);
	index = -1;
	while (path_splitted[++index])
	{
		aux = ft_strjoin(path_splitted[index], "/");
		if (aux == NULL)
		{
			free_split(path_splitted);
			return (NULL);
		}
		free(path_splitted[index]);
		path_splitted[index] = aux;
	}
	return (path_splitted);
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
			return (0);
		if (access(binary, F_OK) == 0 && access(binary, X_OK) == -1)
			return (error_msg(COMM_NPERM, command));
		free(binary);
	}
	return (error_msg(COMM_NFOUND, command));
}

int	check_binary(char *command, char **paths)
{
	char			*binary;

	if (isBuiltin(command))
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

	if (ft_strchr(command, '/') || isBuiltin(command))
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
