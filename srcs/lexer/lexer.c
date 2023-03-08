/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:19:08 by javmarti          #+#    #+#             */
/*   Updated: 2023/03/07 19:19:08 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_list	*tokenize(char *_input)
{
	t_input	input;
	
	input = init_input(_input);
	while (input.str[input.index] != '\0')
	{
		while (is_space(input.str[input.index]))
			input.index++;
		input.token_start = &input.str[input.index];
		while (is_space(input.str[input.index]) == 0)
		{
			if (input.str[input.index++] == '"')
			{
				if (input.between_marks == 1)
					input.between_marks = 0;
				else
					input.between_marks = 1;
			}
		}
		input.token_len = (size_t)(&input.str[input.index] - input.token_start);
		if (input.token_len > 0 && add_new_token_lst(&input) == -1)
			return (NULL);
	}
	free(input.str);
	return (input.token_lst);
}

static t_input	init_input(char *_input)
{
	t_input	input;

	input.str = _input;
	input.len = ft_strlen(input.str);
	input.index = 0;
	input.token_lst = NULL;
	input.between_marks = 0;
	return (input);
}

static int	add_new_token_lst(t_input *input)
{
	char	*token;

	token = (char *)ft_calloc(input->token_len + 1, sizeof(char));
	if (token == NULL)
	{
		ft_lstclear(&input->token_lst, free);
		return (-1);
	}
	ft_strlcpy(token, input->token_start, input->token_len + 1);
	ft_lstadd_back(&input->token_lst, ft_lstnew((void *)token));
	return (0);
}
