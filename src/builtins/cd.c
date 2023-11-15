/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:06:32 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/14 12:42:22 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int	ft_cd_home(t_shell_data **shell_data)
{
	int		exit_code;
	char	*home;

	home = ft_envp_get_value((*shell_data)->envp, "HOME"); // voir que faire si la var home n'existe pas
	if (!home[0])
	{
		ft_putendl_fd("bash: cd: « HOME » is not defined", 2);
		return (1);
	}
	exit_code = chdir(home);
	if (exit_code)
	{
		perror("bash: cd");
		return (exit_code);
	}
	return (ft_change_pwds(shell_data));
}

static
int	ft_cd_oldpwd(t_shell_data **shell_data)
{
	char	*oldpwd;
	int		exit_code;

	if (ft_env_has((*shell_data)->envp, "OLDPWD"))
	{
		oldpwd = ft_envp_get_value((*shell_data)->envp, "OLDPWD");
		exit_code = access(oldpwd, F_OK);
		if (exit_code)
			return (ft_cd_errors(oldpwd, ": No such file or directory\n"));
		exit_code = chdir(oldpwd);
		if (exit_code)
			return (ft_cd_errors(oldpwd, ": Not a directory\n"));
		ft_pwd();
		return (ft_change_pwds(shell_data));
	}
	ft_perror("bash: cd: OLDPWD not set\n");
	return (1);
}

static
int	ft_cd_path(t_shell_data **shell_data, char *path)
{
	int		exit_code;

	if (ft_isequal(path, "-"))
		return (ft_cd_oldpwd(shell_data));
	exit_code = access(path, F_OK);
	if (exit_code)
		return (ft_cd_errors(path, ": No such file or directory\n"));
	exit_code = chdir(path);
	if (exit_code)
	{
		if (errno == EACCES)
			return (ft_cd_errors(path, ": Permission denied\n"));
		return (ft_cd_errors(path, ": Not a directory\n"));
	}
	return (ft_change_pwds(shell_data));
}

int	ft_cd(t_shell_data **shell_data, t_cmd *cmd)
{
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putendl_fd("bash: cd: too many arguments.", 2);
		return (1);
	}
	if (cmd->args[1] && ft_strlen(cmd->args[1]) >= 256)
		return (ft_cd_errors(cmd->args[1], ": File name too long\n"));
	if (!cmd->args[1] || ft_isequal(cmd->args[1], "~"))
		return (ft_cd_home(shell_data));
	return (ft_cd_path(shell_data, cmd->args[1]));
}

