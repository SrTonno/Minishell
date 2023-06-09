/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:41:38 by javmarti          #+#    #+#             */
/*   Updated: 2023/04/27 18:41:38 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

int	ft_pwd(void)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	if (wd == NULL)
	{
		ft_putstr_fd("ERROR: pwd: couldn't read working directory\n",
			STDERR_FILENO);
		exit(-1);
	}
	else
	{
		ft_printf("%s\n", wd);
		free(wd);
	}
	exit(0);
}
