/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:13:54 by tvillare          #+#    #+#             */
/*   Updated: 2023/04/01 15:06:25 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIN_H
# define BIN_H

# include <stdio.h>
# include <stdlib.h>

# include "libft.h"


# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39

int		find_mod_env(char **env, char **comand);
int		find_env(char **env, char *str);
int		len_doble(char **str);
int		len_doble_base(char **str);
int		to_future(char **str, int i);
int		len_doble_uniq_one(char **str, char **env);
int		find_char(char *str, char c);
int		find_env_basic(char **env, char *str);
char	*replace_env(int	len, char *org, char *add, int mark);
int		find_var(char *str);

#endif

