/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:13:30 by javmarti          #+#    #+#             */
/*   Updated: 2023/04/26 18:13:30 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

static char	*get_path(int length, char *txt_path);

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
		fprintf(stderr, "-bash: cd: too many arguments\n");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	path = get_path(length, ast_node->command[1]);
	if (chdir(path) < 0)
	{
		fprintf(stderr, "-bash: cd: %s: No such file or directory\n",
			ast_node->command[1]);
		return (1);
	}
	// actualizar OLDPWD
	// actualizar PWD
	return (0);
}

static char	*get_path(int length, char *txt_path)
{
	char	*path;

	if (length == 1)
		path = getenv("HOME");
	else if (ft_strncmp("-", txt_path, 2) == 0)
		path = getenv("OLDPWD");
	else
		path = txt_path;
	return (path);
}
