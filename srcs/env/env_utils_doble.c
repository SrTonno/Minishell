/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_doble.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:07:31 by tvillare          #+#    #+#             */
/*   Updated: 2023/04/28 20:26:56 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	len_doble(char **str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i] != NULL)
		if (ft_strchr(str[i], '=') != NULL && to_future(str, i) == -1)
			count++;
	return (count);
}

int	len_doble_base(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}
