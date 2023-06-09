/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:21:33 by javmarti          #+#    #+#             */
/*   Updated: 2023/04/28 20:21:33 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"
# include "ft_printf.h"

# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39

char	*replace_env(int len, char *org, char *add, int status);
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
char	**malloc_env(char **env);

void	free_split(char **str);
void	print_export(char **env);
int		copy_num(int status, char *dst, int j);
char	*check_shlvl(char *str);

#endif
