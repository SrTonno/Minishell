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
 void	free_triple(char ***str)
 {
	free_split(str[0]);
	free(str);
	return ;

 }
