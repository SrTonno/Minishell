/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:59:34 by tvillare          #+#    #+#             */
/*   Updated: 2023/06/27 16:02:01 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <termios.h>
#include <stdio.h>

void	free_split(char **split)
{
	int	index;

	index = -1;
	while (split[++index])
		free(split[index]);
	free(split);
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

void	redir_free(void *ptr)
{
	t_redir_type	*redir;

	redir = (t_redir_type *)ptr;
	free(redir->text);
	free(redir);
	return ;
}
