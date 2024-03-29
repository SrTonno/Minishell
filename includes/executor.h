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

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "ast.h"
# include "error_msg.h"
# include "bin.h"
# include "contantes.h"

# define TEMP_FILE ".temp"

char	*get_path_envp(char *envp[]);
char	**get_paths_envp(char *envp[]);
char	**create_paths(char *envp[]);
int		check_binary(char *command, char **paths);
char	*find_binary(char *filename, char **paths);

int		parse_redir(t_list *ast_node, char ***env);

int		create_heredoc(char *delimiter, char ***env, int *mode);
char	*do_heredoc(char *delimitator, char ***env, int *mode);

void	free_split(char **split);

int		handle_exe_error(int error, char *str);

void	handler_fork(int signum);
void	handler_status_print(int status);

void	is_heredoc_last(t_ast_node *ast_node, t_list *redir);

char	*expand_heredoc(char *input, char ***env, int flag);

int		code_status(t_list *ast, char **paths, char ***envp);
int		exec_child(t_list *ast, char **paths, char ***envp);
int		check_str(char *s1, char *s2);

#endif
