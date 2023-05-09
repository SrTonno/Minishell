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

int	ft_cd(t_ast_node *ast_node, char **envp)
{
	char	*cwd;
	char	*path;
	int		length;

	length = 0;
	while (ast_node->command[length])
		length++;
	if (length > 2)
	{
		ft_putstr_fd("-bash: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (chdir(ast_node->command[1]) < 0)
	{
		ft_putstr_fd("-bash: cd: ", STDERR_FILENO);
		ft_putstr_fd(ast_node->command[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	// actualizar OLDPWD
	free(cwd);
	cwd = getcwd(NULL, 0);
	// actualizar PWD
	free(cwd);
	return (0);
}
