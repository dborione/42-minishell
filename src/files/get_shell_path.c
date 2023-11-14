/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:06:48 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/14 10:57:18 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_get_shell_path(char **envp, char *shell_name)
{
	char	*absolute_shell_path;
	char	*pwd;
	char	*tmp;

	tmp = NULL;
	pwd = ft_envp_get_value(envp, "PWD");
	if (!ft_endswith(pwd, "/"))
	{
		tmp = ft_strjoin(pwd, "/");
		if (!tmp)
			return (NULL);
		pwd = tmp;
	}
	absolute_shell_path = ft_strjoin(pwd, &shell_name[2]);
	if (tmp)
		free(tmp);
	return (absolute_shell_path);
}
