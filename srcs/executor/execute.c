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

int	exec_command(t_list *ast, t_ast_node *ast_node, char ***envp)
{
	if (ast_node->index != 0 || ast->next != NULL)
		return (0);
	if (ft_strncmp(ast_node->binary, "export", 7) == 0)
		return (ft_export(envp, ast_node->command));
	if (ft_strncmp(ast_node->binary, "unset", 6) == 0)
		return (ft_unset(envp, ast_node->command));
	if (ft_strncmp(ast_node->binary, "cd", 3) == 0)
		return (ft_cd(ast_node, envp));
	return (0);
}

int	exec_command_child(t_ast_node *ast_node, char **envp)
{
	if (ft_strncmp(ast_node->binary, "pwd", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(ast_node->binary, "echo", 5) == 0)
		return (ft_echo(ast_node));
	else if (ft_strncmp(ast_node->binary, "env", 4) == 0)
		return (ft_env(envp));
	else
	{
		execve(ast_node->binary, ast_node->command, envp);
		exit(0);
	}
	return (0);
}

int	create_child(t_ast_node *ast_node, char **envp)
{
	pid_t	pid;
	int		heredoc_fd;

	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		if (ast_node->input_fd != STDIN_FILENO)
		{
			dup2(ast_node->input_fd, STDIN_FILENO);
			close(ast_node->input_fd);
		}
		if (ast_node->output_fd != STDOUT_FILENO)
		{
			dup2(ast_node->output_fd, STDOUT_FILENO);
			close(ast_node->output_fd);
		}
		exec_command_child(ast_node, envp);
	}
	return (0);
}

int	exec_child(t_list *ast, char **paths, char ***envp)
{
	int			status;
	t_ast_node	*ast_node;

	status = parse_redir(ast);
	ast_node = (t_ast_node *)ast->content;
	if (status == 0)
	{
		status = check_binary(ast_node->command[0], paths);
		if (status == 0)
		{
			ast_node->binary = find_binary(ast_node->command[0], paths);
			if (ast_node->binary == NULL)
				return (error_msg(MALLOC_ERROR, NULL));
			if (is_no_child_builtin(ast_node->binary))
				status = exec_command(ast, ast_node, envp);
			else
			{
				if (create_child(ast_node, *envp) == -1)
					return (error_msg(FORK_ERR, NULL));
				waitpid(-1, &status, 0);
			}
		}
	}
	return (status);
}

int	execute(t_list *ast, char **envp[])
{
	char		**paths;
	t_ast_node	*ast_node;
	int			status;

	paths = create_paths(*envp);
	if (paths == NULL)
		return (error_msg(MALLOC_ERROR, NULL));
	while (ast != NULL)
	{
		ast_node = (t_ast_node *)ast->content;
		status = exec_child(ast, paths, envp);
		unlink(TEMP_FILE);
		if (ast_node->input_fd != STDIN_FILENO)
			close(ast_node->input_fd);
		if (ast_node->output_fd != STDOUT_FILENO)
			close(ast_node->output_fd);
		ast = ast->next;
	}
	free_split(paths);
	return (status);
}
