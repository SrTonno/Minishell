/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 20:11:29 by javmarti          #+#    #+#             */
/*   Updated: 2023/05/03 20:11:29 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

int	isBuiltin(char *command)
{
	if (ft_strncmp(command, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(command, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(command, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(command, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(command, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(command, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(command, "exit", 5) == 0)
		return (1);
	return (0);
}

int	isNoChildBuiltin(char *command)
{
	if (ft_strncmp(command, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(command, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(command, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(command, "exit", 5) == 0)
		return (1);
	return (0);
}
