/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:19:24 by javmarti          #+#    #+#             */
/*   Updated: 2023/06/27 18:30:57 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	is_heredoc_last(t_ast_node *ast_node, t_list *redir)
{
	t_redir_type	*redir_type;
	int				flag;

	flag = 0;
	while (redir)
	{
		redir_type = redir->content;
		if (redir_type->type == HEREDOC)
			flag = 1;
		else if (redir_type->type == INFILE)
			flag = 0;
		redir = redir->next;
	}
	if (flag)
		ast_node->input_fd = ast_node->heredoc_fd;
}

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
