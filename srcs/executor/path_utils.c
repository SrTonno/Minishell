/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:19:24 by javmarti          #+#    #+#             */
/*   Updated: 2023/06/25 18:51:25 by tvillare         ###   ########.fr       */
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

int	wait_pids(t_list *ast)
{
	int			status;
	t_ast_node	*ast_node;

	while (ast)
	{
		ast_node = ast->content;
		waitpid(ast_node->pid, &status, 0);
		ast = ast->next;
	}
	return (status);
}

void	delete_file(t_ast_node *ast_node) //funciona pero rebiar ubicacion
{
	if (ast_node->output_fd == 1 && ast_node->mode == 1)
	{
		unlink(TEMP_FILE);
		ast_node->input_fd = open(TEMP_FILE, \
			O_CREAT | O_RDONLY | O_TRUNC, S_IRWXU);
	}
}
