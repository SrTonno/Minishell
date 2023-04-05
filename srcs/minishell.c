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

/*
Eroor cuando poner en el unset 2 palabras Parecidas ej: "tr" "tractor"
*/

int	main(int argc, char *argv[], char **env)
{
	char				*input;
	char				**new_env;
	struct sigaction	sa;
	t_list				*token_lst;

	(void)argc;
	(void)argv;
	env = malloc_env(env);
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	//if (sigaction(SIGINT, &sa, NULL) == -1)
		//printf("Error\n");
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		printf("Error2\n");
	while (1)
	{
		/*input = readline(PROMPT);
		ctr_d(input, NULL);
		if (ft_strncmp(input, "\0", 1) == 0)
			continue ;
		add_history(input);
		//while (find_var(input) >= 0)
			//input = env_expand(env, input);
		printf("FIN -> %s\n", input);
		if (ft_strncmp(input, "exit", 5) == 0)
			break ;
		token_lst = tokenize(input);
		if (token_lst == NULL)
			break ;
		print_lst(token_lst);
		ft_lstclear(&token_lst, free);*/
		//ft_env(env);
		new_env = malloc_env(env);
		//new_env = ft_export(new_env, ft_split("export bob=po tr=poi =a LESS=aaaaaaaaaaaasasasaasjfgkfg unset=1 sggsetyarytsdf saUos=p i o=h i hah= p=oi u=p as=pop yuy=pap y=4 s sfdffs bob=p tr=FINNNN pepe=josse pepe=paco", ' '));
		//new_env = ft_export(new_env, ft_split("export tono=Antonio MAc=caca caca=MAC tr=MOD USER=TONO asds =pass TERM=BuenosDias", ' '));
		//ft_env(env);
		//printf("-------------\n");
		//env = ft_unset(env, ft_split("unset tr tractor= LESS unset saUos as tractor y tr",  ' ')); //unset as  sasos tractor LESS= as  zpapapa
		new_env = ft_unset(new_env, ft_split("unset MallocNanoZone PWD LANG= LESS ASFASaadd ZSH HOME SHELL COMMAND_MODE PATH XPC_SERVICE_NAME",  ' '));
		ft_env(new_env);
		new_env = ft_unset(new_env, ft_split("unset MallocNanoZone PWD= ZDOTDIR _ GIT_ASKPASS LANG LESS ZSH HOME SHELL ddss TERM_PROGRAM LSCOLORS COMMAND_MODE PATH",  ' '));
		//printf("---------------------------##############################-------------------------------------------------\n");
		ft_env(new_env);
		//free(input);
		printf("FINN comand\n");
	}
	free(input);
	return (0);
}
