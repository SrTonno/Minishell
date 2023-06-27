/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:51:57 by javmarti          #+#    #+#             */
/*   Updated: 2023/06/26 16:51:57 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# define STRING 1
# define METACHAR 2

typedef struct s_token
{
	char	*token;
	int		token_type;
}	t_token;

void	free_token(void *token_node);

#endif