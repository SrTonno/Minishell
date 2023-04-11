/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:48:49 by javmarti          #+#    #+#             */
/*   Updated: 2023/03/13 21:48:49 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	syntax_error(char *str);

int	handle_par_error(int error, char *str)
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
		ft_putstr_fd("-bash: ", STDOUT_FILENO);
		ft_putstr_fd(str, STDOUT_FILENO);
		ft_putstr_fd(": No such file or directory", STDOUT_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		status = 1;
	}
	return (status);
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
