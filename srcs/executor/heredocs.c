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

	printf("%s\n", delimitator);
	text = (char *)ft_calloc(1, sizeof(char));
	ft_printf("> ");
	line = get_next_line(STDIN_FILENO);
	//printf("%s\n", line);
	if (line == NULL)
		return(free(text), NULL);
	while (ft_strncmp(line, delimitator, ft_strlen(delimitator) + 1) != 0 && g_status != 130 && line != NULL)
	{
		write(1,"> ", 1);
		aux = text;
		if (line != NULL)
		{
			text = ft_strjoin(text, line);
			free(aux);
			free(line);
		}
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	return (text);
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
