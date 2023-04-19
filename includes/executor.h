/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:39:54 by javmarti          #+#    #+#             */
/*   Updated: 2023/03/07 15:39:54 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "ast.h"
# include "error_msg.h"

# define TEMP_FILE ".temp"

typedef struct s_exec_child
{
	char	**command;
	char	*binary;
	int		infile;
	int		outfile;
	int		*pipe_fd;
}	t_exec_child;

char	*get_path_envp(char *envp[]);
char	**get_paths_envp(char *envp[]);
int		check_binary(char *command, char **paths);
char	*find_binary(char *filename, char **paths);

int		create_heredocs(char **heredocs);
char	*do_heredoc(char *delimitator);

void	free_split(char **split);

int		handle_exe_error(int error, char *str);

#endif
