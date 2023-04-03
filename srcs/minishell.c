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
		ctr_d(input, env);
		if (ft_strncmp(input, "\0", 1) == 0)
			continue ;
		add_history(input);
		while (find_var(input) >= 0)
			input = env_expand(env, input);
		printf("FIN -> %s\n", input);
		if (ft_strncmp(input, "exit", 5) == 0)
			break ;
		token_lst = tokenize(input);
		if (token_lst == NULL)
			break ;
		print_lst(token_lst);
		ft_lstclear(&token_lst, free);
		env = ft_export(env, ft_split("export as=p tractor=red LESS=aaaaaaaaaaaasasasaasjfgkfg unset=1 sasos=p i o=h i hah= p=oi u=p yuy=pap tr=re y=4 bob=p", ' '));
		//ft_env(env);
		printf("-------------\n");
		env = ft_unset(env, ft_split("unset as tr= USER iuppppp yuy= hah", ' '));
		//printf("HEY\n");
		ft_env(env);
		free(input);
	}
	free(input);
	return (0);
}
