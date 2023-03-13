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

# define PROMPT "\033[0;33mminish>> \033[0m"

typedef struct s_ast_node
{
	char				**command;
	struct s_ast_node	*next;
}	t_ast_node;

void	handler(int signum);
void	ctr_d(char *input);

t_list	*tokenize(char *input);

t_ast_node	*parser(t_list *list);
void	free_ast(t_ast_node *ast);

#endif
