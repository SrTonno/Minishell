/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 18:06:52 by javmarti          #+#    #+#             */
/*   Updated: 2023/04/02 18:06:52 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	create_child(t_ast_node ast_node, char **envp)
{
	pid_t	pid;
	int		heredoc_fd;

	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
	{
		heredoc_fd = create_heredocs(ast_node.heredocs);
		if (ast_node.input_fd == -1 && heredoc_fd != -1)
			dup2(heredoc_fd, STDIN_FILENO);
		else
		{
			dup2(ast_node.input_fd, STDIN_FILENO);
			close(ast_node.input_fd);
		}
		close(heredoc_fd);
		dup2(ast_node.output_fd, STDOUT_FILENO);
		if (ast_node.output_fd != STDOUT_FILENO)
			close(ast_node.output_fd);
		execve(ast_node.binary, ast_node.command, envp);
	}
	return (0);
}

void	close_fds(t_ast_node *ast_node)
{
	if (ast_node->input_fd == -1)
		unlink(TEMP_FILE);
	else if (ast_node->input_fd != STDIN_FILENO)
		close(ast_node->input_fd);
	if (ast_node->output_fd != STDOUT_FILENO)
		close(ast_node->output_fd);
	return ;
}

int	execute(t_ast_node *ast, char *envp[])
{
	char	**paths;
	char	*binary;
	int		status;

	paths = get_paths_envp(envp);
	if (paths == NULL)
		return (1);
	while (ast != NULL)
	{
		status = check_binary(ast->command[0], paths);
		if (status == 0)
		{
			binary = find_binary(ast->command[0], paths);
			if (binary == NULL)
				return (handle_exe_error(MALLOC_ERR, NULL));
			ast->binary = binary;
			if (create_child(*ast, envp) == 1)
				return (handle_exe_error(FORK_ERR, NULL));
			waitpid(-1, &status, 0);
		}
		close_fds(ast);
		ast = ast->next;
	}
	return (status);
}
