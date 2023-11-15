/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 01:18:21 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/15 22:26:28 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int		ft_init_pwd(t_shell_data *shell_data)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, PATH_MAX))
	{
		perror("cd: error retrieving current directory:"
		" getcwd: cannot access parent directories");
		return (0);
	}
	shell_data->pwd = ft_strdup(cwd);
	if (!shell_data->pwd)
		return (0);
	return (1);
}

int		ft_init_all(t_shell_data **shell_data, char *shell_path, char *envp[])
{
	if (!ft_init_shell(shell_data, shell_path, envp))
	{
		perror("bash");
		return (0);
	}
	if (!ft_init_pwd(*shell_data))
		return (0);
	ft_init_shell_sigaction(*shell_data, MAIN);
	return (1);
}
