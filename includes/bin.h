/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:13:54 by tvillare          #+#    #+#             */
/*   Updated: 2023/04/02 15:48:44 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIN_H
# define BIN_H

# include <stdio.h>
# include <stdlib.h>

# include "libft.h"


# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39

char	*replace_env(int	len, char *org, char *add);
int		len_doble(char **str);
int		len_doble_base(char **str);
int		len_doble_invert(char **str);
int		len_doble_uniq_one(char **str, char **env, int mode);
int		to_future(char **str, int i);
int		find_char(char *str, char c);
int		find_env_basic(char **env, char *str);
int		find_mod_env(char **env, char **comand);
int		find_env(char **env, char *str);
int		find_var(char *str);
int		find_var_end(char *str, int i);
int		export_util(char **env, char **comand);
int		find_env_len(char **env, char *str);
#endif

