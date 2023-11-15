/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pwds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:08:19 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/15 14:02:45 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int	ft_change_oldpwd(t_shell_data **shell_data)
{
	char	*old_path;
	char	*last_pwd;

	if (!ft_env_has((*shell_data)->envp, "PWD"))
	{
		if (ft_envp_unset(shell_data, "OLDPWD")
			&& ft_private_envp_unset(shell_data, "OLDPWD"))
			return (0);
		return (1);
	}
	last_pwd = ft_envp_get_value((*shell_data)->envp, "PWD");
	old_path = ft_strjoin("OLDPWD=", last_pwd);
	if (!old_path)
		return (127);
	if (!ft_envp_set(shell_data, old_path)
		|| !ft_private_envp_set(shell_data, old_path))
	{
		free(old_path);
		return (127);
	}
	free(old_path);
	return (0);
}

static
int	ft_change_pwd(t_shell_data **shell_data, char *cwd)
{
	char	*new_pwd;

	new_pwd = ft_strjoin("PWD=", cwd);
	if (!new_pwd)
		return (127);
	if (!ft_envp_set(shell_data, new_pwd)
		|| !ft_private_envp_set(shell_data, new_pwd))
	{
		free(new_pwd);
		return (127);
	}
	free(new_pwd);
	return (0);
}

int	ft_change_pwds(t_shell_data **shell_data)
{
	int		exit_code;
	char	cwd[PATH_MAX];

	exit_code = ft_change_oldpwd(shell_data);
	if (exit_code)
		return (exit_code);
	if (!getcwd(cwd, PATH_MAX))
	{
		perror("cd: error retrieving current directory:"
		"getcwd: cannot access parent directories");
		return (1);
	}
	return (ft_change_pwd(shell_data, cwd));
}
