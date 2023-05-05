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

# define PROMPT "\033[0;33mminish>> \033[0m"

int		handle_input(char *input, char **envp[]);

void	handler(int signum);
void	ctr_d(char *input, char **env);

t_list	*tokenize(char *inputLine);

t_list	*parse(t_list *list);
void	free_ast(t_list *ast);

int		execute(t_list *ast, char *envp[]);

void	free_split(char **str);

char	**ft_export(char **env, char **comand);
char	***malloc_env(char **env);
void	ft_env(char **env);
char	**ft_unset(char **env, char **comand);
char	*env_expand(char ***env, char *input);
int		find_var(char *str);

int		export_env(char ***env, char **coman);
int		unset_env(char ***env, char **comand);

#endif
