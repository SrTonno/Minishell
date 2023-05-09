/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:38:03 by javmarti          #+#    #+#             */
/*   Updated: 2023/05/09 15:38:03 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#include "ft_printf.h"

int		count_quotes(char *input);
void	clean_quotes(char **new_input, char *input);

char	*remove_quotes(char *input)
{
	char	*new_input;
	int		count;
	char	*copy;

	if (input == NULL)
		return (NULL);
	count = count_quotes(input);
	if (count == 0)
		return (input);
	new_input = (char *)ft_calloc(ft_strlen(input) - count + 1, sizeof(char));
	if (new_input == NULL)
		return (NULL);
	clean_quotes(&new_input, input);
	free(input);
	return (new_input);
}

void	clean_quotes(char **new_input, char *input)
{
	int		size;
	char	quote;

	size = -1;
	while (input[++size])
	{
		if (input[size] == SINGLE_QUOTE || input[size] == DOUBLE_QUOTE)
		{
			quote = input[size];
			ft_strlcat(*new_input, input, ft_strlen(*new_input) + size + 1);
			input += (size + 1);
			size = -1;
			while (input[++size] != quote)
				;
			ft_strlcat(*new_input, input, ft_strlen(*new_input) + size + 1);
			input += (size + 1);
			size = -1;
		}
	}
	ft_strlcat(*new_input, input, ft_strlen(*new_input) + size + 1);
}

int	count_quotes(char *input)
{
	int		count;
	char	quote;

	count = 0;
	while (*input)
	{
		if (*input == SINGLE_QUOTE || *input == DOUBLE_QUOTE)
		{
			quote = *input;
			count += 2;
			while (*(++input) != quote)
				input++;
		}
		input++;
	}
	return (count);
}
