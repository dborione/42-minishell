/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:52:52 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 16:43:08 by dborione         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_free_str_and_return(char *str1, char *str2)
{
	if (str1)
		free (str1);
	if (str2)
		free (str2);
	return (NULL);
}

static char	*ft_join_and_free(char *tmp_user_path, char *str2)
{
	char	*joined_str;

	joined_str = ft_strjoin(tmp_user_path, str2);
	if (!joined_str)
		return (NULL);
	return (joined_str);
}

static char	*ft_change_user_colour(char *user, char *colour)
{
	char	*tmp_user;

	tmp_user = ft_strjoin(colour, user);
	if (!tmp_user)
		return (NULL);
	return (tmp_user);
}

static char	*ft_print_user_path(char *user, char *host, char *path, int home)
{
	char	*tmp_path;
	char	*tmp_user_path;
	char	*tmp_prompt;
	char	*prompt;

	tmp_path = ft_strjoin("~", path);
	if (!tmp_path)
		return (ft_free_str_and_return(user, NULL));
	tmp_user_path = ft_strjoin(user, host);
	if (!tmp_user_path)
		return (ft_free_str_and_return(user, tmp_path));
	if (home)
		tmp_prompt = ft_join_and_free(tmp_user_path, tmp_path);
	else
		tmp_prompt = ft_join_and_free(tmp_user_path, path);
	free(tmp_path);
	free(tmp_user_path);
	if (!tmp_prompt)
		return (ft_free_str_and_return(user, NULL));
	prompt = ft_strjoin(tmp_prompt, "\x1b[37m$ ");
	free (tmp_prompt);
	if (!prompt)
		return (ft_free_str_and_return(user, NULL));
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
	if (!path)
		return (NULL);
	home = ft_envp_get_value(envp, "HOME");
	user = ft_change_user_colour(user, "\x1b[32m");
	if (!user)
		return (NULL);
	if (ft_startswith(path, home))
	{
		len = ft_strlen(home);
		if (!path[len])
			return (ft_print_user_path(user, 
					"\x1b[32m@student.s19.be\x1b[37m:\x1b[34m", "", 1));
		else if (path[len] == '/')
			return (ft_print_user_path(user, 
					"\x1b[32m@student.s19.be\x1b[37m:\x1b[34m", &path[len], 1));
	}
	return (ft_print_user_path(user, 
			"\x1b[32m@student.s19.be\x1b[37m:\x1b[34m", path, 0));
}
