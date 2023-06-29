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

int	wait_pids(t_list *ast);

int	exec_command(t_ast_node *ast_node, char ***envp)
{
	if (ft_strncmp(ast_node->binary, "export", 7) == 0)
		return (ft_export(envp, ast_node->command));
	if (ft_strncmp(ast_node->binary, "unset", 6) == 0)
		return (ft_unset(envp, ast_node->command));
	if (ft_strncmp(ast_node->binary, "cd", 3) == 0)
		return (ft_cd(ast_node, envp));
	if (ft_strncmp(ast_node->binary, "exit", 5) == 0)
		return (ft_exit(ast_node->command));
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
		exit(1);
	}
	return (0);
}

int	create_child(t_ast_node *ast_node, char **envp)
{
	ast_node->pid = fork();
	handler_fork(!ast_node->pid);
	if (ast_node->pid < 0)
		return (-1);
	else if (ast_node->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (ast_node->pipe_fd != NULL)
			close(ast_node->pipe_fd[0]);
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
		if (is_no_child_builtin(ast_node->binary))
			exec_command(ast_node, &envp);
		exec_command_child(ast_node, envp);
	}
	return (0);
}

int	exec_child(t_list *ast, char **paths, char ***envp)
{
	int			status;
	t_ast_node	*ast_node;

	status = parse_redir(ast, envp);
	ast_node = (t_ast_node *)ast->content;
	if (status == 0 && g_status != 130 && g_status != 2)
	{
		status = check_binary(ast_node->command[0], paths);
		if (status == 0)
		{
			ast_node->binary = find_binary(ast_node->command[0], paths);
			if (ast_node->binary == NULL)
				return (error_msg(MALLOC_ERROR, NULL));
			if (is_valid_no_child_builtin(ast, ast_node->binary))
				status = exec_command(ast_node, envp);
			else
			{
				if (create_child(ast_node, *envp) == -1)
					return (error_msg(FORK_ERR, NULL));
			}
		}
	}
	return (status);
}

int	execute(t_list *ast, char **envp[])
{
	t_list		*ast_copy;
	char		**paths;
	t_ast_node	*ast_node;

	paths = create_paths(*envp);
	if (paths == NULL)
		return (error_msg(MALLOC_ERROR, NULL));
	ast_copy = ast;
	while (ast != NULL && g_status != -3)
	{
		ast_node = (t_ast_node *)ast->content;
		g_status = code_status(ast, paths, envp);
		unlink(TEMP_FILE);
		if (ast_node->input_fd != STDIN_FILENO)
			close(ast_node->input_fd);
		if (ast_node->output_fd != STDOUT_FILENO)
			close(ast_node->output_fd);
		ast = ast->next;
	}
	if (g_status == -3)
		return (1);
	wait_pids(ast_copy);
	free_split(paths);
	return (g_status);
}
