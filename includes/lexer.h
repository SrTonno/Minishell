/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:40:26 by javmarti          #+#    #+#             */
/*   Updated: 2023/03/07 15:40:26 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include <stdio.h>
# include <stdlib.h>

# include "libft.h"

typedef struct s_input
{
	char	*str;
	size_t	len;
	size_t	index;
	char	*token_start;
	size_t	token_len;
	int		between_marks;
	t_list	*token_lst;
}	t_input;

static t_input	init_input(char *_input);
static int		add_new_token_lst(t_input *input);

int	is_special_char(unsigned char c);
int	is_space(unsigned char c);

#endif
