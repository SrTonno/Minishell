/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:24:00 by javmarti          #+#    #+#             */
/*   Updated: 2023/04/10 17:24:00 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int		clean_input(char **input, char ***env);
int		find_var(char *str, int mode);
char	*env_expand(char ***env, char *input, int mode);

int	loop_heredoc(char **text, char **line, char ***env, int expand_flag)
{
	char	*tmp;
	char	*aux;

	tmp = expand_heredoc(ft_strdup(*line), env, expand_flag);
	if (tmp[ft_strlen(tmp) - 1] != '\n')
	{
		aux = tmp;
		tmp = ft_strjoin(aux, "\n");
		free(aux);
		if (tmp == NULL)
			error_msg(MALLOC_ERROR, NULL);
	}
	aux = *text;
	*text = ft_strjoin(*text, tmp);
	free(aux);
	free(tmp);
	free(*line);
	*line = readline(">");
	return (0);
}

char	*do_heredoc(char *delimitator, char ***env, int *mode)
{
	char	*text;
	char	*line;
	int		expand_flag;

	text = (char *)ft_calloc(1, sizeof(char));
	line = readline(">");
	expand_flag = 1;
	if (*delimitator == '"')
	{
		expand_flag = 0;
		delimitator++;
	}
	while (line != NULL && check_str(line, delimitator) != 0)
		loop_heredoc(&text, &line, env, expand_flag);
	if (line == NULL)
	{
		*mode = 1;
		return (text);
	}
	return (free(line), text);
}

int	child_heredoc(char *delimiter, char ***env, int *mode, int fd)
{
	pid_t	pid;
	char	*text;

	pid = fork();
	handler_fork(!pid);
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		text = do_heredoc(delimiter, env, mode);
		ft_putstr_fd(text, fd);
		free(text);
		exit (0);
	}
	waitpid(pid, &g_status, 0);
	return (0);
}

int	create_heredoc(char *delimiter, char ***env, int *mode)
{
	int		heredoc_fd;

	heredoc_fd = open(TEMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (heredoc_fd < 0)
		return (heredoc_fd);
	child_heredoc(delimiter, env, mode, heredoc_fd);
	close(heredoc_fd);
	heredoc_fd = open(TEMP_FILE, O_RDONLY);
	return (heredoc_fd);
}

int	do_heredocs(t_ast_node *ast_node, char ***env)
{
	t_list			*redir;
	t_redir_type	*redir_type;
	int				mode;

	mode = 0;
	redir = ast_node->redir;
	while (redir)
	{
		redir_type = redir->content;
		if (redir_type->type == HEREDOC && g_status != 2)
		{
			if (ast_node->heredoc_fd != STDIN_FILENO)
				close(ast_node->heredoc_fd);
			ast_node->heredoc_fd = create_heredoc(redir_type->text, env, &mode);
			if (ast_node->heredoc_fd == -1)
				return (-1);
			ast_node->mode = mode;
		}
		redir = redir->next;
	}
	return (0);
}
