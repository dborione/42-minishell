/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_command_fds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:52:20 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/15 13:45:06 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_set_command_fds(t_shell_data **shell_data, t_cmd *cmds)
{
	t_cmd	*target;

	if (!cmds)
		return ;
	target = cmds;
	while (target->next)
		target = target->next;
	target->input_fd = (*shell_data)->input_fd;
	(*shell_data)->input_fd = STDIN_FILENO;
	target->output_fd = (*shell_data)->output_fd;
	(*shell_data)->output_fd = STDOUT_FILENO;
}
