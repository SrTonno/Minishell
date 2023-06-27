/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:10:54 by javmarti          #+#    #+#             */
/*   Updated: 2023/04/21 13:10:54 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	do_heredocs(t_ast_node *ast_node, char ***env);

int	do_redir_out(t_redir_type *redir_type, t_ast_node *ast_node)
{
	int	fd;

	if (access(redir_type->text, F_OK) == 0
		&& access(redir_type->text, W_OK) == -1)
		return (error_msg(PERM_ERR, redir_type->text));
	if (redir_type->type == OVERWRITE)
	{
		fd = open(redir_type->text, O_CREAT | O_TRUNC | O_WRONLY);
		if (fd == -1)
			return (error_msg(NO_FILE_ERROR, redir_type->text));
		if (ast_node->output_fd != STDOUT_FILENO)
			close(ast_node->output_fd);
		ast_node->output_fd = fd;
	}
	else if (redir_type->type == APPEND)
	{
		fd = open(redir_type->text, O_CREAT | O_APPEND | O_WRONLY);
		if (fd == -1)
			return (error_msg(NO_FILE_ERROR, redir_type->text));
		if (ast_node->output_fd != STDOUT_FILENO)
			close(ast_node->output_fd);
		ast_node->output_fd = fd;
	}
	return (0);
}

int	do_redir(t_redir_type *redir_type, t_ast_node *ast_node)
{
	int	fd;

	if (redir_type->type == INFILE)
	{
		if (access(redir_type->text, F_OK) == -1)
			return (error_msg(NO_FILE_ERROR, redir_type->text));
		if (access(redir_type->text, R_OK) == -1)
			return (error_msg(PERM_ERR, redir_type->text));
		fd = open(redir_type->text, O_RDONLY);
		if (fd == -1)
			return (error_msg(NO_FILE_ERROR, redir_type->text));
		if (ast_node->input_fd != STDIN_FILENO)
			close(ast_node->input_fd);
		ast_node->input_fd = fd;
	}
	return (do_redir_out(redir_type, ast_node));
}

int	is_pipe_necessary(t_list *ast)
{
	if (ast->next == NULL)
		return (0);
	return (1);
}

int	create_pipe(t_list *ast)
{
	int			*pipe_fd;
	t_ast_node	*ast_node;

	pipe_fd = (int *)ft_calloc(2, sizeof(int));
	if (pipe_fd == NULL)
		return (error_msg(MALLOC_ERROR, NULL));
	if (pipe(pipe_fd) == -1)
		return (error_msg(PIPE_ERROR, NULL));
	ast_node = (t_ast_node *)ast->content;
	ast_node->pipe_fd = pipe_fd;
	if (ast_node->mode == 0)
	ast_node->output_fd = pipe_fd[WRITE_END];
	ast_node = (t_ast_node *)ast->next->content;
	ast_node->input_fd = pipe_fd[READ_END];
	return (0);
}

int	parse_redir(t_list *ast, char ***env)
{
	t_list			*redir;
	t_ast_node		*ast_node;
	int				status;

	status = 0;
	if (ast == NULL || ast->content == NULL)
		return (status);
	if (is_pipe_necessary(ast))
		if (create_pipe(ast) != 0)
			return (error_msg(MALLOC_ERROR, NULL));
	ast_node = (t_ast_node *)ast->content;
	signal(SIGINT, SIG_IGN);
	status = do_heredocs(ast_node, env);
	redir = ast_node->redir;
	while (redir)
	{
		if (redir->content != NULL)
			status = do_redir((t_redir_type *)redir->content,
					ast_node);
		if ((status != 0 && status != -2) || g_status == 130)
			break ;
		redir = redir->next;
	}
	is_heredoc_last(ast_node, ast_node->redir);
	return (status);
}
