/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:07:36 by javmarti          #+#    #+#             */
/*   Updated: 2023/04/18 18:07:36 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_msg.h"

int	syntax_error(char *str);

int	handle_par_error(int error, char *str)
{
	int	status;

	status = 0;
	if (error == PERM_ERR)
	{
		ft_putstr_fd("-bash: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Permision denied", STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		status = 1;
	}
	else if (error == SYNTAX_ERROR)
		status = syntax_error(str);
	else if (error == NO_FILE_ERROR)
	{
		ft_putstr_fd("-bash: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory", STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		status = 1;
	}
	return (status);
}

int	malloc_error(void)
{
	ft_putstr_fd("fatal error\n", STDERR_FILENO);
	return (-1);
}

int	syntax_error(char *str)
{
	if (str == NULL)
		ft_putstr_fd("-bash: syntax error near unexpected token 'newline'\n", \
			STDERR_FILENO);
	else
	{
		ft_putstr_fd("-bash: syntax error near unexpected token `", \
			STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	return (2);
}

int	check_metachars(t_list *token_lst)
{
	char	*c;

	while (token_lst)
	{
		c = token_lst->content;
		if (is_special(*c))
		{
			if (*c == '|' && ft_strlen(c) != 1)
				return (handle_par_error(SYNTAX_ERROR, c + 1));
			else if ((*c == '<' || *c == '>')
				&& ft_strlen(c) == 2 && *c != *(c + 1))
				return (handle_par_error(SYNTAX_ERROR, c + 1));
			else if ((*c == '<' || *c == '>') && ft_strlen(c) > 2)
				return (handle_par_error(SYNTAX_ERROR, c + 2));
		}
		token_lst = token_lst->next;
	}
	return (0);
}

int	check_text_after_metachars(t_list *token_lst)
{
	char	*c;

	while (token_lst)
	{
		c = token_lst->content;
		if (*c == '|')
		{
			if (token_lst->next == NULL)
				return (handle_par_error(SYNTAX_ERROR, NULL));
			if (*(char *)token_lst->next->content == '|')
				return (handle_par_error(SYNTAX_ERROR, 
					token_lst->next->content));
		}
		else if (*c == '<' || *c == '>')
		{
			if (token_lst->next == NULL)
				return (handle_par_error(SYNTAX_ERROR, NULL));
			else if (is_special(*(char *)token_lst->next->content))
				return (handle_par_error(SYNTAX_ERROR,
					token_lst->next->content));
		}
		token_lst = token_lst->next;
	}
	return (0);
}
