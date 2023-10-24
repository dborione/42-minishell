/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:52:52 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/24 15:54:04 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void ft_free_str_and_exit(char *str)
{
	free (str);
	exit (1); // a voir
}

static char	*ft_join_and_free(char *tmp_user_path, char *str2, char *tmp_path)
{
	char *joined_str;

	joined_str = ft_strjoin(tmp_user_path, str2);
	if (!joined_str)
	{
		free (tmp_user_path);
		free (tmp_path);
		exit (1); // a voir
	}
	return (joined_str);
}

static char *ft_change_user_colour(char *user, char *colour)
{
	char *tmp_user;

	tmp_user = ft_strjoin(colour, user);
	if (!tmp_user)
		exit (1); //protect
	return (tmp_user);
}

static char	*ft_print_user_path(char *user, char *host, char *path, int home)
{
	char *tmp_path;
	char *tmp_user_path;
	char *tmp_prompt;
	char *prompt;

	tmp_path = ft_strjoin("~", path);
	if (!tmp_path)
		exit (1); // a voir
	tmp_user_path = ft_strjoin(user, host);
	if (!tmp_user_path)
		ft_free_str_and_exit(tmp_path);
	if (home)
		tmp_prompt = ft_join_and_free(tmp_user_path, tmp_path, tmp_path);
	else
		tmp_prompt = ft_join_and_free(tmp_user_path, path, tmp_path);
	free(tmp_path);
	free(tmp_user_path);
	prompt = ft_strjoin(tmp_prompt, "\x1b[37m$ ");
	free (tmp_prompt);
	if (!prompt)
		exit (1); //a voir
	free(user);
	return (prompt);

}

char	*ft_show_user_path(char **envp)
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
		user = ft_change_user_colour(user, "\x1b[32m");
		len = ft_strlen(home);
		if (!path[len])
			return (ft_print_user_path(user, "\x1b[32m@student.s19.be\x1b[37m:\x1b[34m", "", 1));
		else if (path[len] == '/')
			return (ft_print_user_path(user, "\x1b[32m@student.s19.be\x1b[37m:\x1b[34m", &path[len], 1));
	}
	return (ft_print_user_path(user, "\x1b[32m@student.s19.be\x1b[37m:\x1b[34m", path, 0));
}

