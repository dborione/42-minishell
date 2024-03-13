/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pwds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:08:19 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 17:12:15 by dborione         ###   ########.fr       */
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
int	ft_cwd_failed(t_shell_data *shell_data, char *target_dir)
{
	char	*tmp;

	if (!shell_data->pwd)
		return (127);
	tmp = ft_strjoin(shell_data->pwd, "/");
	if (!tmp)
		return (127);
	free(shell_data->pwd);
	shell_data->pwd = ft_strjoin(tmp, target_dir);
	free(tmp);
	if (!shell_data->pwd)
		return (127);
	return (0);
}

static
int	ft_save_pwd(t_shell_data *shell_data, char *new_pwd)
{
	if (shell_data->pwd)
		free(shell_data->pwd);
	shell_data->pwd = ft_strdup(new_pwd);
	if (!shell_data->pwd)
		return (1);
	return (0);
}

static
int	ft_change_pwd(t_shell_data **shell_data, char *target_dir)
{
	char	cwd[PATH_MAX];
	char	*new_pwd;

	if (!getcwd(cwd, PATH_MAX))
	{
		perror("cd: error retrieving current directory:"
			" getcwd: cannot access parent directories");
		return (ft_cwd_failed(*shell_data, target_dir));
	}
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
	return (ft_save_pwd(*shell_data, cwd));
}

int	ft_change_pwds(t_shell_data **shell_data, char *target_dir)
{
	int		exit_code;

	exit_code = ft_change_oldpwd(shell_data);
	if (exit_code)
		return (exit_code);
	return (ft_change_pwd(shell_data, target_dir));
}
