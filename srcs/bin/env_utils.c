/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:50:23 by tvillare          #+#    #+#             */
/*   Updated: 2023/03/30 14:38:02 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

int	to_future(char **str, int i)
{
	int		base;
	int		len;

	base = i;
	len = find_char(str[base], '=');
	while (str[++i] != '\0')
		if (len == find_char(str[i], '=') && ft_strncmp(str[base], str[i], len) == 0)
			return(i);
	return (-1);
}

