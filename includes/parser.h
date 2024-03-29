/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:40:16 by javmarti          #+#    #+#             */
/*   Updated: 2023/03/07 15:40:16 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>

# include "ast.h"
# include "error_msg.h"
# include "contantes.h"
# include "token.h"

typedef struct s_len_ast
{
	int	len;
	int	meta;
}	t_len_ast;

t_list		*mov_to_next_list(t_list *list, int num);
t_ast_node	*list_to_char(t_list *list, t_len_ast max, int index);

int			handle_par_error(int error, char *str);

int			check_metachars(t_list *token_list);
int			check_text_after_metachars(t_list *token_lst);
int			check_files(t_list *token_lst);

int			is_special(unsigned char c);

void		free_ast(t_ast_node *ast);

#endif
