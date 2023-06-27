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

# include "libft.h"
# include "contantes.h"
# include "token.h"

# define READ_END 0
# define WRITE_END 1

# define INFILE 0
# define HEREDOC 1
# define OVERWRITE 3
# define APPEND 4

typedef struct s_redir_type
{
	char	*text;
	int		type;
}	t_redir_type;

typedef struct s_ast_node
{
	int		index;
	char	**command;
	t_list	*redir;
	char	*binary;
	int		input_fd;
	int		output_fd;
	int		*pipe_fd;
	pid_t	pid;
	int		mode;
}	t_ast_node;

void	free_ast_node(void *ptr);
void	redir_free(void *ptr);

#endif
