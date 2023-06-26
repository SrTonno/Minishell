/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:43:12 by javmarti          #+#    #+#             */
/*   Updated: 2023/04/25 18:43:12 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSG_H
# define ERROR_MSG_H

# include <unistd.h>
# include <stddef.h>

# include "libft.h"
# include "contantes.h"

# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39

# define PERM_ERR 1
# define SYNTAX_ERROR 2
# define NO_FILE_ERROR 3
# define COMM_NFOUND 4
# define COMM_NPERM 5
# define MALLOC_ERROR 6
# define NO_FILE_DIR 7
# define FORK_ERR 8
# define PIPE_ERROR 9

int	check_syntax_after_metachars(t_list *token_lst);
int	check_syntax_metachars(t_list *token_lst);
int	check_quotes(char *input);
int	error_msg(int error, char *str);

int	is_special(unsigned char c);

#endif
