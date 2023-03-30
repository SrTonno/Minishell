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

int	main(int argc, char *argv[], char **env)
{
	char				*input;
	struct sigaction	sa;
	t_list				*token_lst;

	(void)argc;
	(void)argv;
	env = malloc_env(env);
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
		ctr_d(input);
		if (ft_strncmp(input, "exit", 5) == 0)
			break ;
		if (ft_strncmp(input, "\0", 1) == 0)
			continue ;
		add_history(input);
		token_lst = tokenize(input);
		if (token_lst == NULL)
			break ;
		print_lst(token_lst);
		ft_lstclear(&token_lst, free);
		env = ft_export(env, ft_split("a as=p  LESS=aaaaaaaaaaaasasasaasjfgkfg sasos=p i o=h i hah= p=oi u=p tr=p tr=re y=4 tractor=red", ' '));
		int u;
		u = 0;
		while (env[u] != '\0')
			printf("%s\n", env[u++]);
		free(input);
	}
	free(input);
	return (0);
}
