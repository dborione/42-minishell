/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_output_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:47:14 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/07 16:18:53 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
void	ft_set_cmd_outfile_fd(
	t_shell_data **shell_data, t_cmd *cmds, int fd)
{
	t_cmd	*target;

	target = cmds;
	while (target && target->next)
		target = target->next;
	if (!target || (*shell_data)->pipes > target->id)
	{
		if ((*shell_data)->output_fd != -1
			&& (*shell_data)->output_fd != STDOUT_FILENO)
			close((*shell_data)->output_fd);
		(*shell_data)->output_fd = fd;
	}
	else
	{
		if (target->output_fd != -1
			&& target->output_fd != STDOUT_FILENO)
			close(target->output_fd);
		target->output_fd = fd;
	}
}

int	ft_get_outfile(t_shell_data **shell_data, t_cmd *cmds, char *outfile_path)
{
	int	fd;

	fd = open(outfile_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_set_cmd_outfile_fd(shell_data, cmds, fd);
	if (fd == -1)
	{
		(*shell_data)->exit_code = EXIT_FAILURE;
		return (0);
	}
	return (1);
}
