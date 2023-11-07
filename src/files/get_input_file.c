/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:46:57 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/07 17:07:57 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
void	ft_set_cmd_infile_fd(
	t_shell_data **shell_data, t_cmd *cmds, int fd)
{
	t_cmd	*target;

	target = cmds;
	while (target && target->next)
		target = target->next;
	if (!target || (*shell_data)->pipes > target->id)
	{
		if ((*shell_data)->input_fd != -1
			&& (*shell_data)->input_fd != STDIN_FILENO)
			close((*shell_data)->input_fd);
		(*shell_data)->input_fd = fd;
	}
	else
	{
		if (target->input_fd != -1
			&& target->input_fd != STDIN_FILENO)
			close(target->input_fd);
		target->input_fd = fd;
	}
}

int		ft_get_infile(
	t_shell_data **shell_data, t_cmd *cmds, char *infile_path)
{
	int	fd;

	//ft_printf("infile: %s\n", infile_path);
	if (access(infile_path, F_OK) == 0 && access(infile_path, R_OK) == 0)
	{
		fd = open(infile_path, O_RDONLY, 0644);
		ft_set_cmd_infile_fd(shell_data, cmds, fd);
		if (fd == -1)
		{
			(*shell_data)->exit_code = EXIT_FAILURE;
			return (0);
		}
		(*shell_data)->infile = 1;
		return (1);
	}
	ft_set_cmd_infile_fd(shell_data, cmds, -1);
	return (0);
}
