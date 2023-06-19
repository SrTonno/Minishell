/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 12:36:37 by tvillare          #+#    #+#             */
/*   Updated: 2023/06/19 20:23:50 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <termios.h>

void	*ex_calloc(size_t count, size_t size)
{
	void	*var;

	var = ft_calloc(count, size);
	if (var == NULL)
		exit(0);
	return (var);
}

void	redir_free(void *ptr)
{
	t_redir_type	*redir;

	redir = (t_redir_type *)ptr;
	free(redir->text);
	free(redir);
	return ;
}

void	free_ast_node(void *ptr)
{
	t_ast_node	*ast_node;

	ast_node = (t_ast_node *)ptr;
	free_split(ast_node->command);
	free(ast_node->pipe_fd);
	free(ast_node->binary);
	ft_lstclear(&ast_node->redir, redir_free);
	free(ast_node);
	return ;
}

void	disable_ctrl_c_print(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}
