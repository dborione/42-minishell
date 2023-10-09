/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:52:52 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/04 14:21:10 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_print_user_path(char *user, char *host, char *path, int home)
{
	if (home)
		return (ft_printf(
				"\033[0;32m%s@%s\033[0;37m:\033[0;34m~%s\033[0;37m$\033[0m",
				user, host, path));
	return (ft_printf(
			"\033[0;32m%s@%s\033[0;37m:\033[0;34m%s\033[0;37m$\033[0m",
			user, host, path));
}

int	ft_show_user_path(char **envp)
{
	char	*user;
	char	*path;
	char	*home;
	size_t	len;

	user = ft_envp_get_value(envp, "USER");
	path = ft_envp_get_value(envp, "PWD");
	home = ft_envp_get_value(envp, "HOME");
	if (ft_startswith(path, home))
	{
		len = ft_strlen(home);
		if (!path[len])
			return (ft_print_user_path(user, "student.s19.be", "~", 1));
		else if (path[len] == '/')
			return (ft_print_user_path(user, "student.s19.be", &path[len], 1));
	}
	return (ft_print_user_path(user, "student.s19.be", path, 0));
}
