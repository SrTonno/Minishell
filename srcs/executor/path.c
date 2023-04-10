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

int	check_binary(char *command, char **paths)
{
	int		index;
	char	*binary;

	if (ft_strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (0);
		if (access(command, X_OK) == -1)
			return (handle_exe_error(COMM_NPERM, command));
		return (handle_exe_error(NO_FILE_DIR, command));
	}
	index = -1;
	while (paths[++index])
	{
		binary = ft_strjoin(paths[index], command);
		if (binary == NULL)
			return (handle_exe_error(MALLOC_ERR, NULL));
		if (access(binary, X_OK) == 0)
			return (0);
		if (access(binary, F_OK) == 0 && access(binary, X_OK) == -1)
			return (handle_exe_error(COMM_NPERM, command));
		free(binary);
	}
	return (handle_exe_error(COMM_NFOUND, command));
}

char	*find_binary(char *command, char **paths)
{
	int		index;
	char	*binary;

	if (ft_strchr(command, '/'))
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
