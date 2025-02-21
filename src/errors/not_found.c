/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_found.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 22:56:43 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/16 11:57:44 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_command_not_found(char *cmd_name)
{
	char	*message;

	ft_putstr_fd("bash: ", STDERR_FILENO);
	message = ft_strjoin(cmd_name, ": command not found\n");
	if (message)
	{
		ft_perror(message);
		free(message);
	}
}

void	ft_no_such_file(char *cmd_name)
{
	char	*message;

	ft_putstr_fd("bash: ", STDERR_FILENO);
	message = ft_strjoin(cmd_name, ": No such file or directory\n");
	if (message)
	{
		ft_perror(message);
		free(message);
	}
}

void	ft_perm_denied(char *cmd_name)
{
	char	*message;

	ft_putstr_fd("bash: ", STDERR_FILENO);
	message = ft_strjoin(cmd_name, ": Permission denied\n");
	if (message)
	{
		ft_perror(message);
		free(message);
	}
}
