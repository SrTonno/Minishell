/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:13:54 by tvillare          #+#    #+#             */
/*   Updated: 2023/06/26 11:11:24 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIN_H
# define BIN_H

# include <stdio.h>
# include <stdlib.h>
# include "contantes.h"

# include "libft.h"
# include "ft_printf.h"
# include "ast.h"
# include "error_msg.h"

int		ft_pwd(void);
int		ft_cd(t_ast_node *ast_node, char ***envp);
int		ft_echo(t_ast_node *ast_node);
int		ft_env(char **env);
int		ft_unset(char ***env, char **command);
int		ft_export(char ***env, char **comand);
int		ft_exit(char **command);

int		is_builtin(char *command);
int		is_no_child_builtin(char *command);

int		find_env_basic(char **env, char *str);

void	free_split(char **str);

#endif
