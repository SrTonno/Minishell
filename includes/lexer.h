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

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdlib.h>

# include "libft.h"

# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39

typedef struct s_lexer
{
	char	*str;
	size_t	len;
	size_t	index;
	char	*token_start;
	size_t	token_len;
	t_list	*token_lst;
}	t_lexer;

t_lexer	init_lexer(char *inputLine);
int		add_new_token_lst(t_lexer *lexer);
int		any_env_var_str(char *str);

int		handle_char(t_lexer *lexer);

int		is_special(unsigned char c);
int		is_space(unsigned char c);
int		is_env_var_char(unsigned char c);

#endif
