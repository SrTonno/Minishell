/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:33:29 by javmarti          #+#    #+#             */
/*   Updated: 2023/03/07 15:33:29 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURC
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# include "libft.h"
# include "ast.h"
# include "error_msg.h"
# include "env.h"
# include "contantes.h"

# define PROMPT "\033[0;33mminish>> \033[0m"

void	handle_input(char *input, char **envp[]);

void	handler(void);
int		ctr_d(char *input);

void	loop(char **env);

t_list	*tokenize(char *inputLine);

t_list	*parse(t_list *list);
void	free_ast(t_list *ast);

int		execute(t_list *ast, char **envp[]);

void	free_split(char **str);

char	**malloc_env(char **env);
void	ft_env(char **env);
char	*env_expand(char ***env, char *input, int mode);
int		find_var(char *str, int mode);
void	ft_exit(int exitCode);

#endif
