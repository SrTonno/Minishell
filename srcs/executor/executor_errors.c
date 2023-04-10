/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:47:40 by javmarti          #+#    #+#             */
/*   Updated: 2023/04/09 22:47:40 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// xpf -> Command 'xpf' not found -> 127
// /xpf -> -bash: /xpf: No such file or directory -> 127
// /usr/ -> -bash: /usr/: Is a directory -> 126
// /usr -> -bash: /usr: Is a directory -> 126
// ./minishell sin permiso -> -bash: ./minishell: Permission denied -> 126

static void	handle_exec_error2(int error, char *str, int *status);

int	handle_exe_error(int error, char *str)
{
	int	status;

	status = 0;
	if (error == COMM_NFOUND)
	{
		ft_putstr_fd("Command '", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("' not found\n", STDERR_FILENO);
		status = 127;
	}
	else if (error == COMM_NPERM)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		status = 126;
	}
	handle_exec_error2(error, str, &status);
	return (status);
}

static void	handle_exec_error2(int error, char *str, int *status)
{
	if (error == NO_FILE_DIR)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		*status = 126;
	}
	else if (error == MALLOC_ERR)
	{
		ft_putstr_fd("error allocating memory\n", STDERR_FILENO);
		*status = 1;
	}
	else if (error == FORK_ERR)
	{
		ft_putstr_fd("fork error\n", STDERR_FILENO);
		*status = 1;
	}
}
