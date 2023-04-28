/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:07:23 by javmarti          #+#    #+#             */
/*   Updated: 2023/04/26 19:07:23 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

int		is_flag(char *str);
void	print_args(char *argv[]);

int	ft_echo(t_ast_node *ast_node)
{
	int	length;

	length = 0;
	while (ast_node->command[length])
		length++;
	if (length == 1)
		ft_printf("\n");
	else
	{
		if (is_flag(ast_node->command[1]))
			print_args(ast_node->command + 2);
		else
		{
			print_args(ast_node->command + 1);
			ft_printf("\n");
		}
	}
	exit (0);
}

void	print_args(char *argv[])
{
	while (*argv)
	{
		ft_printf("%s", *(argv++));
		if (*argv)
			ft_printf(" ");
	}
	return ;
}

int	is_flag(char *str)
{
	if (*str == '-')
	{
		while (*(++str) == 'n')
			;
		if (*str == '\0')
			return (1);
	}
	return (0);
}
