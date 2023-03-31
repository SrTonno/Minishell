/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:50:23 by tvillare          #+#    #+#             */
/*   Updated: 2023/03/31 17:24:07 by tvillare         ###   ########.fr       */
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

char	*replace_env(int len, char *org, char *add, int mark)
{
	int	i;
	int	j;
	int	a;
	int	meta;
	char *dst;

	dst = ft_calloc(len + 1, sizeof(char));
	i = 0;
	j = 0;
	meta = 0;

	while (len > j)
	{
		if (i == mark)
		{
			if (add != NULL)
			{

				a = find_char(add, '=') + 1;
				printf("add(%d)\n", a);
				while (add[a] != '\0')
					dst[j++] = add[a++];

			}
			while (org[i] != ' ' && org[i] != '\0')
					i++;
			printf("FIN\n");
		}
		else
			dst[j++] = org[i++];
		printf("%s (len->%d, i->%d)\n", dst, len, i);
	}
	return (dst);
}

