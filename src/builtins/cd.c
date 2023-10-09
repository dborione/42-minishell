/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:06:32 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/06 18:01:23 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static
int	ft_cd_home(char **envp)
{
	char	*tmp;

	tmp = ft_strjoin("PWD=", ft_envp_get_value(envp, "HOME"));
	ft_printf("cd hoome %s\n", tmp);
	if (!tmp)
		return (127);
	if (!ft_envp_set(envp, &tmp))
	{
		free(tmp);
		return (127);
	}
	free(tmp);
	return (0);
}

// static
// char	*ft_get_absolute_path(char **envp, char *shell_name)
// {
// 	char	*absolute_shell_path;
// 	char	*pwd;
// 	char	*tmp;

// 	tmp = NULL;
// 	pwd = ft_envp_get_value(envp, "PWD");
// 	if (!ft_endswith(pwd, "/"))
// 	{
// 		tmp = ft_strjoin(pwd, "/");
// 		if (!tmp)
// 			return (NULL);
// 		pwd = tmp;
// 	}
// 	absolute_shell_path = ft_strjoin(pwd, shell_name);
// 	if (tmp)
// 		free(tmp);
// 	return (absolute_shell_path);
// }

// static
// int	ft_cd_path(char **envp, char *path)
// {
// 	//char	*tmp;

// 	// if (!ft_envp_set(envp, ''))
// 	// 	return (127);
// 	return (0);
// }

int	ft_cd(char **envp, char *input)
{
	char	**args;

	args = ft_split(input, ' ');
	if (!args)
		return (127);
	if (!args[1])
	{
		ft_free_split(args);
		return (ft_cd_home(envp));
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
