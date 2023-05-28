/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlevel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:52:45 by tvillare          #+#    #+#             */
/*   Updated: 2023/05/28 17:31:06 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	get_sign(char **str)
{
	if (*(*str) == '-')
	{
		(*str)++;
		return (-1);
	}
	else if (*(*str) == '+')
		(*str)++;
	return (1);
}

static int	ft_atoi_shlevel(const char *str)
{
	int				sign;
	long int		num;

	if (*str == '\0' || str == 0)
		return (0);
	sign = get_sign((char **)&str);
	num = 0;
	if (sign == -1)
		return (0);
	while (*str)
	{
		if (ft_isdigit(*str) == 0 && *str != '\0')
			return (1);
		if (num * sign > 9223372036854775807 / 10)
			return (1);
		num *= 10;
		num += *(str++) - '0';
	}
	return (num + 1);
}

char	*check_shlvl(char *str)
{
	char	*var;
	int		num;
	char	*chr;

	num = ft_atoi_shlevel(str + 6);
	var = ft_itoa(num);
	chr = ft_strjoin("SHLVL=", var);
	free(var);
	return (chr);
}
