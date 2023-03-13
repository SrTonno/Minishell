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

# define PERM_ERR 1
# define SYNTAX_ERROR 2
# define NO_FILE_ERROR 3

typedef struct s_ast_node
{
	char				**command;
	struct s_ast_node	*next;
}	t_ast_node;

t_ast_node	*find_end_ast(t_ast_node *ast);
t_list		*mov_to_next_list(t_list *list, int num);

int			handle_error(int error, char *str);

int			check_metachars(t_list *token_list);
int			check_text_after_metachars(t_list *token_lst);
int			check_files(t_list *token_lst);

int			is_special(unsigned char c);

#endif
