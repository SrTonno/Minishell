/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:36:08 by javmarti          #+#    #+#             */
/*   Updated: 2023/03/07 15:36:08 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ctr_d(char *input)
{
	if (input == NULL) //ctr+D
	{
		rl_replace_line("exit", 0);
		//rl_redisplay();
		exit (0);
	}
}
int	main(void)
{
	char	*input;
	struct	sigaction sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1) //(Ctrl-C)
		printf("Error\n");
	if (sigaction(SIGQUIT, &sa, NULL) == -1) //(Ctrl-/)
		printf("Error\n");
	while (1)
	{
		input = readline(PROMPT);
		ctr_d(input);
		add_history(input);
		printf("%s\n", input);
		free(input);
	}
	return (0);
}
