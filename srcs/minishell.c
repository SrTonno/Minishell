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
	//env = malloc_env(env);
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
		//new_env = malloc_env(env);
		//new_env = export_env(new_env, ft_split("export bob=po tr=poi =a LESS=aaaaaaaaaaaasasasaasjfgkfg unset=1 sggsetyarytsdf saUos=p i o=h i hah= p=oi u=p as=pop yuy=pap y=4 s sfdffs bob=p tr=FINNNN pepe=josse pepe=paco", ' '));
		//ft_env(new_env);
		//new_env = ft_unset(new_env, ft_split("unset MallocNanoZone PWD= bob ZDOTDIR _ GIT_ASKPASS LANG LESS ZSH HOME SHELL ddss TERM_PROGRAM LSCOLORS COMMAND_MODE PATH",  ' '));

		////printf("---------------------------##############################-------------------------------------------------\n");
		//env = export_env(env, ft_split("export a paco=nickname LES=PA LESSS=GOG USER=paco maria=a bob=po tr=poi =a unset=1 sggsetyarytsdf saUos=p i o=h i hah= p=oi u=p as=pop yuy=pap y=4 s sfdffs bob=p tr=FINNNN pepe=josse pepe=paco nombre=Tono a=ds aASDDW=ASFAF<C", ' '));
		env = export_env(env, ft_split("export Nuevo=new USER=tono  tr=paco tractor=red aass LESS=MORE SHELL=minishell", ' '));
		ft_env(env);
		env = unset_env(env, ft_split("unset Nuevo OLDPWD LESS tr USER NADA", ' '));
		ft_env(env);
		//free(input);

		printf("FINN comand\n");
	}
	free(input);
	return (0);
}
