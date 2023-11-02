/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_found.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 22:56:43 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/02 23:04:35 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_command_not_found(char *cmd_name)
{
	char	*message;

	message = ft_strjoin(cmd_name, ": command not found\n");
	if (message)
	{
		ft_perror(message);
		free(message);
	}
}
