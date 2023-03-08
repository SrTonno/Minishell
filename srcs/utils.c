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

int	is_special_char(unsigned char c)
{
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
