/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:27:34 by tvillare          #+#    #+#             */
/*   Updated: 2023/05/27 19:34:13 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	condicion_rep(char *org, int i)
{
	if (org[i] != '$' && org[i] != ' ' && org[i] != '\0'
		&& org[i - 1] != '?' && org[i] != '/' && org[i] != '>'
		&& org[i] != '<' && org[i] != '|')
		return (1);
	return (0);
}

static int	move_letter_rem(char *org, int i)
{
	while (condicion_rep(org, i))
		i++;
	return (i);
}

static int	replace_var(int j, char *dst, char *add)
{
	int	a;

	if (add != NULL)
	{
		a = find_char(add, '=') + 1;
		while (add[a] != '\0')
			dst[j++] = add[a++];
	}
	return (j);
}

static void	fuck_norminete(int *i, int *j)
{
	*i = 0;
	*j = 0;
}
int	copy_num(int status, char *dst, int j)
{
	char	*num;
	int		i;

	i = 0;
	num = ft_itoa(status);
	while (num[i] != '\0')
		dst[j++] = num[i++];
	free(num);
	return (j);

}
char	*replace_env(int len, char *org, char *add, int status)
{
	int		i;
	int		j;
	char	*dst;
	int		mark;

	fuck_norminete(&i, &j);
	if (len > 0)
		dst = ft_calloc(len + 1, sizeof(char));
	if (dst == NULL || len <= 0)
		return (NULL);
	mark = find_var(org);
	while (len >= j)
	{
		if (i == mark)
		{
			if (org[++i] == '?')
				j = copy_num(status, dst, j);
			else
				j = replace_var(j, dst, add);
			i = move_letter_rem(org, i);
		}
		else
			dst[j++] = org[i++];
	}
	return (dst);
}
