/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:08:06 by tvillare          #+#    #+#             */
/*   Updated: 2023/06/17 19:20:10 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signum)
{
	if (signum == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	/*if (signum == 3)
	{
		//rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}*/
	return ;
}

void	ctr_d(char *input, char **env)
{
	(void)env;
	if (input == NULL)
	{
		rl_replace_line("exit", 0);
		write(1, "exit\n", 5);
		exit (0);
	}
	return ;
}
