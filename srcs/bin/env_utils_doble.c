/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_doble.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:07:31 by tvillare          #+#    #+#             */
/*   Updated: 2023/03/30 15:01:31 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

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
	int	count;

	i = -1;
	count = 0;
	while (str[++i] != NULL)
		if (ft_strchr(str[i], '=') != NULL)
			count++;
	return (count);
}

int	len_doble_uniq_one(char **str, char **env)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i] != '\0')
	{
		if (ft_strchr(str[i], '=') != NULL)
			return (i * -1);
		if(to_future(str, i) == -1 && find_env_basic(env, str[i]) >= 0)
			count++;
	}
	return (count);
}
