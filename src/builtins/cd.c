/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:06:32 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/24 15:54:04 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int	ft_change_oldpwd(t_shell_data **shell_data)
{
	char	*old_path;
	char	*current_pwd;

	current_pwd = ft_envp_get_value((*shell_data)->envp, "PWD");
	old_path = ft_strjoin("OLDPWD=", current_pwd);
	if (!old_path)
		return (EXIT_FAILURE);
	if (!ft_envp_set(shell_data, &old_path))
	{
		free(old_path);
		return (EXIT_FAILURE);
	}
	return (0);
}

static
int	ft_cd_home(t_shell_data **shell_data)
{
	char	*new_path;
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
	exit_code = ft_change_oldpwd(shell_data);
	if (exit_code)
		return (exit_code);
	new_path = ft_strjoin("PWD=", home);
	if (!new_path)
		return (127);
	if (!ft_envp_set(shell_data, &new_path))
	{
		free(new_path);
		return (127);
	}
	return (0);
}

static
int	ft_cd_path(t_shell_data **shell_data, char *path)
{
	char	*new_path;
	char	cwd[PATH_MAX];
	int		exit_code;

	exit_code = access(path, F_OK);
	if (exit_code)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	exit_code = chdir(path);
	if (exit_code)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Not a directory\n", 2);
		return (1);
	}
	exit_code = ft_change_oldpwd(shell_data);
	if (exit_code)
		return (exit_code);
	if (!getcwd(cwd, PATH_MAX))
		return (1);
	new_path = ft_strjoin("PWD=", cwd);
	if (!new_path)
		return (127);
	if (!ft_envp_set(shell_data, &new_path))
	{
		free(new_path);
		return (127);
	}
	return (0);
}

int	ft_cd(t_shell_data **shell_data, t_cmd *cmd)
{
	int res;

	res = 0;
	if (!cmd->args[1] || ft_isequal(cmd->args[1], "~"))
		return (ft_cd_home(shell_data));
	if (ft_isequal(cmd->args[1], "-"))
	{
		res = ft_cd_path(shell_data, ft_envp_get_value((*shell_data)->envp, ft_envp_get_key("OLDPWD")));
		ft_pwd();
		return (res);
	}
	if (cmd->args[2])
	{
		ft_putendl_fd("bash: cd: too many arguments.", 2);
		return (1);
	}
	if (ft_strlen(cmd->args[1]) >= 256)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": File name too long\n", 2);
		return (1);
	}
	return (ft_cd_path(shell_data, cmd->args[1]));
}
