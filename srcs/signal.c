/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:08:06 by tvillare          #+#    #+#             */
/*   Updated: 2023/06/13 12:46:03 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ctr_c(int signum)
{
	(void)signum;
	g_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0),
	rl_redisplay();
}

void	handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctr_c);
}

void	handler_fork(int signum)
{
	if (signum == 1)
		signal(SIGINT, SIG_DFL);
	else
		signal(SIGINT, SIG_IGN);
}

void	ctr_d(char *input, char **env)
{
	(void)env;
	if (input == NULL)
	{
		rl_replace_line("exit", 0);
		write(1, "exit\n", 6);
		exit (0);
	}
	return ;
}

void	handler_status_print()
{
	if (g_status == SIGINT)
	{
		g_status = 130;
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else if (g_status == SIGQUIT)
	{
		g_status = 131;
		ft_putstr_fd("QUIT: 3\n", STDOUT_FILENO);
	}
}
