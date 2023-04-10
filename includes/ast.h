/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 18:02:44 by javmarti          #+#    #+#             */
/*   Updated: 2023/04/02 18:02:44 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# define NOFILE 0
# define OVERWRITE 1
# define APPEND 2

# define READ_END 0
# define WRITE_END 1

typedef struct s_ast_node
{
	char				**command;
	char				*binary;
	int					input_fd;
	int					mode_write;
	int					output_fd;
	char				**heredocs;
	int					*pipe_fd;
	struct s_ast_node	*next;
}	t_ast_node;

#endif
