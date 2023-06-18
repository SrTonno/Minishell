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

char	*do_heredoc(char *delimitator)
{
	char	*text;
	char	*line;
	char	*aux;

	text = (char *)ft_calloc(1, sizeof(char));
	write(1, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	if (line == NULL)
		return (free(text), NULL);
	while (line != NULL && g_status != 130 \
		&& ft_strncmp(line, delimitator, ft_strlen(delimitator) + 1) != 0)
	{
		write(1, "> ", 2);
		aux = text;
		text = ft_strjoin(text, line);
		free(aux);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	if (line == NULL)
		return (free(text), NULL);
	return (free(line), text);
}

int	create_heredoc(char *delimiter)
{
	int		heredoc_fd;
	char	*text;

	heredoc_fd = open(TEMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (heredoc_fd < 0)
		return (heredoc_fd);
	text = do_heredoc(delimiter);
	if (text == NULL)
		return (-2);
	ft_putstr_fd(text, heredoc_fd);
	free(text);
	close(heredoc_fd);
	//if (g_status != 130)
		//return (-1);
	heredoc_fd = open(TEMP_FILE, O_RDONLY);
	return (heredoc_fd);
}

int	do_heredocs(t_ast_node *ast_node)
{
	t_list			*redir;
	t_redir_type	*redir_type;
	int				fd;

	redir = ast_node->redir;
	while (redir)
	{
		redir_type = redir->content;
		if (redir_type->type == HEREDOC)
		{
			fd = create_heredoc(redir_type->text);
			if (fd == -1)
				return (-1);
			if (ast_node->input_fd != STDIN_FILENO)
				close(ast_node->input_fd);
			ast_node->input_fd = fd;
		}
		redir = redir->next;
	}
	return (0);
}
