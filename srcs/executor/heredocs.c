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

char	*expand_heredoc(char *input, char ***env, int flag)
{
	while (find_var(input, 0) >= 0 && flag == 1)
	{
		input = env_expand(env, input, 0);
		if (input == NULL)
			return (NULL);
	}
	return (input);
}

int	loop_heredoc(char **text, char **line, char ***env, int expand_flag)
{
	char	*tmp;
	char	*aux;

	write(1, "> ", 2);
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
	*line = get_next_line(STDIN_FILENO);
	return (0);
}

char	*do_heredoc(char *delimitator, char ***env)
{
	char	*text;
	char	*line;
	int		expand_flag;

	text = (char *)ft_calloc(1, sizeof(char));
	write(1, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	if (line == NULL)
		return (free(text), NULL);
	expand_flag = 1;
	if (*delimitator == '"')
	{
		expand_flag = 0;
		delimitator++;
	}
	while (line != NULL && g_status != 130 \
		&& ft_strncmp(line, delimitator, ft_strlen(delimitator) + 1) != 0)
		loop_heredoc(&text, &line, env, expand_flag);
	if (line == NULL)
		return (free(text), NULL);
	return (free(line), text);
}

int	create_heredoc(char *delimiter, char ***env)
{
	int		heredoc_fd;
	char	*text;

	heredoc_fd = open(TEMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (heredoc_fd < 0)
		return (heredoc_fd);
	text = do_heredoc(delimiter, env);
	if (text == NULL)
		return (-2);
	ft_putstr_fd(text, heredoc_fd);
	free(text);
	close(heredoc_fd);
	heredoc_fd = open(TEMP_FILE, O_RDONLY);
	return (heredoc_fd);
}

int	do_heredocs(t_ast_node *ast_node, char ***env)
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
			fd = create_heredoc(redir_type->text, env);
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
