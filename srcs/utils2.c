/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 12:36:37 by tvillare          #+#    #+#             */
/*   Updated: 2023/06/27 16:00:37 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <termios.h>

int	is_spaced_str(char *input)
{
	while (*input && ft_strchr(" \n\v\r\t", *input))
		input++;
	if (*input == '\0')
		return (1);
	else
		return (0);
}

void	*ex_calloc(size_t count, size_t size)
{
	void	*var;

	var = ft_calloc(count, size);
	if (var == NULL)
		exit(0);
	return (var);
}

void	disable_ctrl_c_print(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}

int	only_space(char *s1)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] != '\n')
	{
		if (s1[i++] != ' ')
			return (1);
	}
	return (0);
}
