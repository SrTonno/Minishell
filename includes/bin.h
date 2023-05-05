/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:13:54 by tvillare          #+#    #+#             */
/*   Updated: 2023/05/05 13:26:52 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIN_H
# define BIN_H

# include <stdio.h>
# include <stdlib.h>

# include "libft.h"
# include "ft_printf.h"
# include "ast.h"

int		ft_pwd(void);
int		ft_cd(t_ast_node *ast_node, char **envp);
int		ft_echo(t_ast_node *ast_node);
int		ft_env(char **env);
int		ft_unset(char ***env, char **command);

int		isBuiltin(char *command);
int		isNoChildBuiltin(char *command);

#endif
