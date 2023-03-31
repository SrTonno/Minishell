/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:04:39 by tvillare          #+#    #+#             */
/*   Updated: 2023/03/31 18:32:23 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_len_ast	count_blocks(t_list *list, int mode)
{
	t_len_ast	command;

	command.len = 1;
	command.meta = 0;
	command.heredocs = 0;
	while (list->next != NULL)
	{
		if (*((unsigned char *)list->content) == '|')
		{
			if (command.len != 1)
				command.len--;
			return (command);
		}
		if (*((unsigned char *)list->content) == '<'
			|| (*((unsigned char *)list->content) == '>') || mode == 1)
		{
			if (*((unsigned char *)list->content) == '<'
				&& ft_strlen(list->content) == 2)
				command.heredocs++;
			command.meta++;
		}
		command.len++;
		list = list->next;
	}
	return (command);
}

static void	new_block_ast(t_ast_node *ast, t_list *list, t_len_ast max)
{
	ast = find_end_ast(ast);
	ast->next = list_to_char(list, max);
}

int	create_pipes(t_ast_node *ast)
{
	if (ast == NULL && ast->next == NULL)
		return (1);
	while (ast->next != NULL)
	{
		if (ast->output_fd == 1 && ast->next->input_fd == 0)
		{
			ast->pipe_fd = (int *)ft_calloc(2, sizeof(int));
			if (ast->pipe_fd == NULL || pipe(ast->pipe_fd))
				return (0);
			ast->output_fd = ast->pipe_fd[WRITE_END];
			ast->next->input_fd = ast->pipe_fd[READ_END];
		}
		ast = ast->next;
	}
	return (1);
}

t_ast_node	*parse(t_list *token_lst)
{
	t_ast_node	*ast;
	t_len_ast	num;

	if (check_metachars(token_lst) != 0
		|| check_text_after_metachars(token_lst) != 0
		|| check_files(token_lst) != 0)
		return (NULL); // NULL está asociado con error, devolver otra cosa porque no es un error que suponga exit del programa
	num = count_blocks(token_lst, 0);
	ast = list_to_char(token_lst, num);
	token_lst = mov_to_next_list(token_lst, num.len);
	while (token_lst != NULL)
	{
		num = count_blocks(token_lst, 0);
		if (*((unsigned char *)token_lst->content) != '|')
			new_block_ast(ast, token_lst, num);
		token_lst = mov_to_next_list(token_lst, num.len);
	}
	create_pipes(ast);
	if (create_pipes(ast) == 0)
	{
		free_ast(ast);
		return (NULL);
	}
	return (ast);
}
