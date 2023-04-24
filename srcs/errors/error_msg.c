/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:07:36 by javmarti          #+#    #+#             */
/*   Updated: 2023/04/18 18:07:36 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_msg.h"
// xpf -> Command 'xpf' not found -> 127
// /xpf -> -bash: /xpf: No such file or directory -> 127
// /usr/ -> -bash: /usr/: Is a directory -> 126
// /usr -> -bash: /usr: Is a directory -> 126
// ./minishell sin permiso -> -bash: ./minishell: Permission denied -> 126

static void	error_msg2(int error, char *str, int *status);
static void	error_msg3(int error, char *str, int *status);

int	error_msg(int error, char *str)
{
	int	status;

	status = 0;
	if (error == COMM_NFOUND)
	{
		ft_putstr_fd("Command '", STDERR_FILENO);
		if (*str == '\0')
			ft_putstr_fd("", STDERR_FILENO);
		else
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
	error_msg2(error, str, &status);
	error_msg3(error, str, &status);
	return (status);
}

static void	error_msg2(int error, char *str, int *status)
{
	if (error == NO_FILE_DIR)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		*status = 126;
	}
	else if (error == FORK_ERR)
	{
		ft_putstr_fd("fork error\n", STDERR_FILENO);
		*status = 1;
	}
}


static int	syntax_error(int error, char *str, int *status)
{
	if (error == SYNTAX_ERROR)
	{
		if (str == NULL)
			ft_putstr_fd("-bash: syntax error near unexpected token \
				'newline'\n", STDERR_FILENO);
		else
		{
			ft_putstr_fd("-bash: syntax error near unexpected token `", \
				STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd("'\n", STDERR_FILENO);
		}
		*status = 2;
	}
}

static void	error_msg3(int error, char *str, int *status)
{
	if (error == PERM_ERR)
	{
		ft_putstr_fd("-bash: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Permision denied", STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		*status = 1;
	}
	else if (error == NO_FILE_ERROR)
	{
		ft_putstr_fd("-bash: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory", STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		*status = 1;
	}
	else if (error == MALLOC_ERROR)
	{
		ft_putstr_fd("fatal error\n", STDERR_FILENO);
		*status = -1;
	}
	syntax_error(error, str, status);
}
