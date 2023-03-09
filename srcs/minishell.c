/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:36:08 by javmarti          #+#    #+#             */
/*   Updated: 2023/03/07 15:36:08 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lst(t_list *lst)
{
	while (lst != NULL)
	{
		printf("%s\n", (char *) lst->content);
		lst = lst->next;
	}
	return ;
}

int	main(void)
{
	char				*input;
	struct sigaction	sa;
	t_list				*token_lst;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		printf("Error\n");
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		printf("Error2\n");
	while (1)
	{
		input = readline(PROMPT);
		if (ft_strncmp(input, "exit", 5) == 0)
			break ;
		if (ft_strncmp(input, "\0", 1) == 0)
			continue ;
		ctr_d(input);
		add_history(input);
		token_lst = tokenize(input);
		if (token_lst == NULL)
			break ;
		print_lst(token_lst);
		ft_lstclear(&token_lst, free);
		free(input);
	}
	free(input);
	return (0);
}
