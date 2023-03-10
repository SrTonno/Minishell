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

#include "minishell.h"


t_ast_node	*find_end_ast(t_ast_node *ast);
t_list		*mov_to_next_list(t_list *list, int num);

#endif
