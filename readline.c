/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:07:10 by tvillare          #+#    #+#             */
/*   Updated: 2023/03/06 12:46:56 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE // Define el macro antes de incluir readline.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
// cc -lreadline main.c

int main()
{
	char *input;

	while (1)
	{
		input = readline("Minish>>: ");
		add_history(input);
		printf("%s\n", input);
		rl_redisplay();
		rl_on_new_line();
		//rl_replace_line("", 0);
		free (input);
	}
	return 0;
}
