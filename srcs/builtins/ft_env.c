/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:15:08 by javmarti          #+#    #+#             */
/*   Updated: 2023/05/02 17:15:08 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "env.h"

static void	print_env(char **env);

int	ft_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		ft_printf("%s\n", env[i]);
	exit(0);
}
