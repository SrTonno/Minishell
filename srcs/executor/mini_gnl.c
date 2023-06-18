/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:43:52 by tvillare          #+#    #+#             */
/*   Updated: 2023/06/13 18:59:18 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*mini_gnl(int fd)
{
	char	*tmp;
	int		numbytes;
	char	*buffer;

	buffer = ft_calloc(1, sizeof(char));
	numbytes = 1;
	tmp = ft_calloc(2, sizeof(char));
	if (tmp == NULL)
		return (NULL);
	while (0 < numbytes && g_status != 130)
	{
		numbytes = read(fd, tmp, 1);
		if (numbytes == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp[numbytes] = '\0';
		buffer = ft_strjoin(buffer, tmp);
		if (ft_strchr(buffer, '\n') != NULL)
			break ;
	}
	free(tmp);
	return (buffer);
}
/*
int	main()
{
	char	*a;
	a = mini_gnl(0);
	printf("%s\n", a);
}
*/
