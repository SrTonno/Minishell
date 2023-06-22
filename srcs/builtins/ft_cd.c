/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:59:16 by javmarti          #+#    #+#             */
/*   Updated: 2023/04/28 17:59:16 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

int	update_env(char ***env, char *env_var, char *value);
int	cd_error_msg(int exitCode, char *msg);

int	ft_cd(t_ast_node *ast_node, char ***envp)
{
	char	*cwd;
	int		length;

	length = 0;
	while (ast_node->command[length])
		length++;
	if (length > 2)
		return (cd_error_msg(1, NULL));
	cwd = getcwd(NULL, 0);
	if (chdir(ast_node->command[1]) < 0)
		return (cd_error_msg(1, ast_node->command[1]));
	if (find_env_basic(*envp, "OLDPWD") != -2 && cwd != NULL)
		update_env(envp, "OLDPWD", cwd);
	free(cwd);
	cwd = getcwd(NULL, 0);
	if (find_env_basic(*envp, "PWD") != -2)
		update_env(envp, "PWD", cwd);
	free(cwd);
	return (0);
}

int	update_env(char ***env, char *env_var, char *value)
{
	char	*export_comm;
	char	*aux;
	char	**command;
	int		status;

	export_comm = ft_strdup("export ");
	aux = ft_strjoin(export_comm, env_var);
	free(export_comm);
	export_comm = aux;
	aux = ft_strjoin(export_comm, "=");
	free(export_comm);
	export_comm = aux;
	aux = ft_strjoin(export_comm, value);
	free(export_comm);
	command = ft_split(aux, ' ');
	free(aux);
	if (command == NULL)
		return (error_msg(MALLOC_ERROR, NULL));
	status = ft_export(env, command);
	free_split(command);
	return (status);
}

int	cd_error_msg(int exitCode, char *msg)
{
	(void)exitCode;
	if (msg == NULL)
		ft_putstr_fd("-bash: cd: too many arguments\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd("-bash: cd: ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	return (1);
}
