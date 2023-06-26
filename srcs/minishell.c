/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:36:08 by javmarti          #+#    #+#             */
/*   Updated: 2023/06/02 17:15:45 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_free(void *ptr);
void	free_ast_node(void *ptr);
void	disable_ctrl_c_print(void);

int	main(int argc, char *argv[], char **env)
{
	(void)argv;
	disable_ctrl_c_print();
	if (argc != 1)
		return (0);
	env = malloc_env(env);
	loop(env);
	return (0);
}

void	loop(char **env)
{
	char	*input;

	g_status = 0;
	while (1)
	{
		handler();
		input = readline(PROMPT);
		add_history(input);
		if (ctr_d(input) == 1)
		{
			free_split(env);
			break ;
		}
		if (is_spaced_str(input))
		{
			free(input);
			continue ;
		}
		handle_input(input, &env);
		if (g_status == -1)
			break ;
	}
	free(input);
	system("leaks -q minishell");
}

int	clean_input(char **input, char ***env)
{
	if (check_quotes(*input) != 0)
	{
		free(*input);
		return (2);
	}
	while (find_var(*input, 1) >= 0)
	{
		*input = env_expand(env, *input, 1);
		if (*input == NULL)
			return (1);
	}
	return (0);
}

int	tokenize_and_parse(char *input, t_list **ast)
{
	t_list	*token_lst;

	token_lst = tokenize(input);
	free(input);
	if (token_lst == NULL)
		return (error_msg(MALLOC_ERROR, NULL));
	if (check_syntax_metachars(token_lst) != 0
		|| check_syntax_after_metachars(token_lst) != 0)
	{
		ft_lstclear(&token_lst, free);
		return (2);
	}
	*ast = parse(token_lst);
	ft_lstclear(&token_lst, free);
	if (*ast == NULL)
		return (error_msg(MALLOC_ERROR, NULL));
	return (0);
}

void	handle_input(char *input, char **env[])
{
	t_list	*ast;

	g_status = clean_input(&input, env);
	if (g_status == 1)
		g_status = 0;
	if (g_status == -1 || g_status == 2)
		return ;
	g_status = tokenize_and_parse(input, &ast);
	if (g_status == -1 || g_status == 2)
		return ;
	g_status = execute(ast, env);
	ft_lstclear(&ast, free_ast_node);
	return ;
}
