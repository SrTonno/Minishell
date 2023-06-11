/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 12:36:37 by tvillare          #+#    #+#             */
/*   Updated: 2023/06/11 12:44:16 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ex_calloc(size_t count, size_t size)
{
	void	*var;

	var = ft_calloc(count, size);
	if (var == NULL)
		exit(0);
	return (var);
}
