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

static void	handle_exec_error2(int error, char *str, int *status);

int	handle_exec_error(int error, char *str)
{
	int	status;

	status = 0;
	if (error == COMM_NFOUND)
	{
		ft_putstr_fd("Command '", STDERR_FILENO);
		if (*str == '\0')
			ft_putstr_fd("''", STDERR_FILENO);
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
	else if (error == FORK_ERR)
	{
		ft_putstr_fd("fork error\n", STDERR_FILENO);
		*status = 1;
	}
}


int	syntax_error(char *str)
{
	if (str == NULL)
		ft_putstr_fd("-bash: syntax error near unexpected token 'newline'\n", \
			STDERR_FILENO);
	else
	{
		ft_putstr_fd("-bash: syntax error near unexpected token `", \
			STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	return (2);
}

int	handle_file_error(int error, char *str)
{
	int	status;

	status = 0;
	if (error == PERM_ERR)
	{
		ft_putstr_fd("-bash: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Permision denied", STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		status = 1;
	}
	else if (error == SYNTAX_ERROR)
		status = syntax_error(str);
	else if (error == NO_FILE_ERROR)
	{
		ft_putstr_fd("-bash: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory", STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		status = 1;
	}
	return (status);
}

int	malloc_error(void)
{
	ft_putstr_fd("fatal error\n", STDERR_FILENO);
	return (-1);
}

int	check_syntax_metachars(t_list *token_lst)
{
	char	*c;

	while (token_lst)
	{
		c = token_lst->content;
		if (is_special(*c))
		{
			if (*c == '|' && ft_strlen(c) != 1)
				return (syntax_error(c + 1));
			else if ((*c == '<' || *c == '>')
				&& ft_strlen(c) == 2 && *c != *(c + 1))
				return (syntax_error(c + 1));
			else if ((*c == '<' || *c == '>') && ft_strlen(c) > 2)
				return (syntax_error(c + 2));
		}
		token_lst = token_lst->next;
	}
	return (0);
}

int	check_syntax_after_metachars(t_list *token_lst)
{
	char	*c;

	while (token_lst)
	{
		c = token_lst->content;
		if (*c == '|')
		{
			if (token_lst->next == NULL)
				return (syntax_error(NULL));
			if (*(char *)token_lst->next->content == '|')
				return (syntax_error(token_lst->next->content));
		}
		else if (*c == '<' || *c == '>')
		{
			if (token_lst->next == NULL)
				return (syntax_error(NULL));
			else if (is_special(*(char *)token_lst->next->content))
				return (syntax_error(token_lst->next->content));
		}
		token_lst = token_lst->next;
	}
	return (0);
}
