/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:13:54 by tvillare          #+#    #+#             */
/*   Updated: 2023/03/30 14:39:58 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIN_H
# define BIN_H

# include <stdio.h>
# include <stdlib.h>

# include "libft.h"

int	find_mod_env(char **env, char **comand);
int	find_env(char **env, char *str);
int	len_doble(char **str);
int	len_doble_base(char **str);
int	to_future(char **str, int i);
int	len_doble_uniq_one(char **str, char **env);
int	find_char(char *str, char c);
int	find_env_basic(char **env, char *str);

#endif

