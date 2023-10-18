/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:06:32 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/18 16:06:47 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	exit_code = chdir(home);
	if (exit_code)
	{
		perror("cd");
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

// static
// char	*ft_get_absolute_path(char **envp, char *shell_name)
// {
// 	char	*absolute_shell_path;
// 	char	*pwd;
// 	char	*new_path;

// 	new_path = NULL;
// 	pwd = ft_envp_get_value(envp, "PWD");
// 	if (!ft_endswith(pwd, "/"))
// 	{
// 		new_path = ft_strjoin(pwd, "/");
// 		if (!new_path)
// 			return (NULL);
// 		pwd = new_path;
// 	}
// 	absolute_shell_path = ft_strjoin(pwd, shell_name);
// 	if (new_path)
// 		free(new_path);
// 	return (absolute_shell_path);
// }

// static
// int	ft_cd_path(char **envp, char *path)
// {
// 	//char	*new_path;

// 	// if (!ft_envp_set(envp, ''))
// 	// 	return (127);
// 	return (0);
// }

int	ft_cd(t_shell_data **shell_data, char *input)
{
	char	**args;

	args = ft_split(input, ' ');
	if (!args)
		return (127);
	if (!args[1])
	{
		ft_free_split(args);
		return (ft_cd_home(shell_data));
	}
	if (args[2])
	{
		ft_putstr_fd("bash: ", 2);
		ft_putendl_fd("too many arguments.", 2);
		return (1);
	}
	//ft_cd_path(envp, args[1]);
	return (0);
}
