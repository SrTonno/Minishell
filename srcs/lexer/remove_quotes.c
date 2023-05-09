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

// int		count_useless_quotes(char *input);
// void	clean_quotes(char **new_input, char *input);

// char	*remove_quotes(char *input)
// {
// 	char	*new_input;
// 	int		new_size;
// 	char	*copy;

// 	if (input == NULL)
// 		return (NULL);
// 	new_size = ft_strlen(input) - count_useless_quotes(input);
// 	// new_input = (char *)ft_calloc(ft_strlen(input) + 1, sizeof(char));
// 	// if (new_input == NULL)
// 	// 	return (NULL);
// 	// clean_quotes(&new_input, input);
// 	// ft_printf("%s|\n", new_input);
// 	// free(input);
// 	return (input);
// }

// int		count_useless_quotes(char *input)
// {
// 	int	count;

// 	count = 0;
// 	while (*input)
// 	{
// 		if (is_quote(*input))
// 		{
// 			input++;
// 			while (*input && is_quote(*input) == 0)
// 			{
// 				if (is_quote(*input)
// 					&& (*(input + 1) || is_quote(*(input + 1))))
// 				{
// 					ft_printf("%s\n", input);
// 					count++;
// 				}
// 				input++;
// 			}
// 		}
// 		input++;
// 	}
// 	ft_printf(">%i\n", count);
// 	return (count);
// }

// void	clean_quotes(char **new_input, char *input)
// {
// 	int		size;
// 	char	quote;

// 	size = -1;
// 	while (input[++size])
// 	{
// 		if (is_quote(input[size]))
// 		{
// 			ft_strlcat(*new_input, input, ft_strlen(*new_input) + size + 1);

// 		}
// 	}
// }
