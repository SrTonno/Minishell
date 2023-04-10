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

# define PROMPT "\033[0;33mminish>> \033[0m"

int			handle_input(char *input, char *envp[]);

void		handler(int signum);
void		ctr_d(char *input);

t_list		*tokenize(char *input);

t_ast_node	*parse(t_list *list);
void		free_ast(t_ast_node *ast);

int			execute(t_ast_node *ast, char *envp[]);

#endif
