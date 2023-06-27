/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 20:17:04 by javmarti          #+#    #+#             */
/*   Updated: 2023/05/03 20:17:04 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	is_numeric_str(char *str);

int	ft_exit(char **command)
{
	int	exit_code;
	int	command_len;

	ft_printf("exit\n");
	command_len = 0;
	while (command[command_len])
		command_len++;
	if (command_len > 2)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", STDERR_FILENO);
		exit (1);
	}
	else if (command_len == 1)
		exit_code = 0;
	else
	{
		if (is_numeric_str(command[1]) == 0)
			exit (2);
		exit_code = ft_atoi(command[1]);
	}
	unlink(TEMP_FILE);
	exit (exit_code);
	return (0);
}

int	is_numeric_str(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
		{
			ft_putstr_fd("bash: exit: numeric argument required\n",
				STDERR_FILENO);
			return (0);
		}
		str++;
	}
	return (1);
}
