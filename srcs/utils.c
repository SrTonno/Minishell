/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 09:39:11 by javmarti          #+#    #+#             */
/*   Updated: 2023/03/08 09:39:11 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	is_env_var_char(unsigned char c)
{
	if (c == '\0')
		return (0);
	if (ft_strchr("?_", c) != NULL || ft_isalnum(c))
		return (1);
	return (0);
}

int	is_special(unsigned char c)
{
	if (c == '\0')
		return (0);
	if (ft_strchr("<>|", c))
		return (1);
	return (0);
}

int	is_space(unsigned char c)
{
	if (ft_strchr(" \n\t", c))
		return (1);
	return (0);
}

void	free_split(char **split)
{
	int	index;

	index = -1;
	while (split[++index])
		free(split[index]);
	free(split);
	return ;
}

void	print_export(char **env)
{
	int	i;
	int	j;
	int	comp;

	i = -1;
	while (env[++i] != NULL)
	{
		j = -1;
		comp = 0;
		printf("declare -x ");
		while (env[i][++j] != '\0')
		{
			printf("%c", env[i][j]);
			if (env[i][j] == '=' && comp == 0)
				comp = printf("\"");
		}
		printf("\"\n");
	}
}

int only_space(char *s1)
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
