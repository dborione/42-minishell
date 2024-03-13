/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:46:57 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 17:20:49 by dborione         ###   ########.fr       */
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

static
int	ft_infile_access(
	t_shell_data **shell_data, t_cmd *cmds, char *infile_path)
{
	int	fd;

	fd = open(infile_path, O_RDONLY, 0644);
	ft_set_cmd_infile_fd(shell_data, cmds, fd);
	if (fd == -1)
	{
		(*shell_data)->exit_code = EXIT_FAILURE;
		return (0);
	}
	return (1);
}

int	ft_get_infile(
	t_shell_data **shell_data, t_cmd *cmds, char *infile_path)
{
	if (access(infile_path, F_OK) == 0 && access(infile_path, R_OK) == 0)
		return (ft_infile_access(shell_data, cmds, infile_path));
	ft_set_cmd_infile_fd(shell_data, cmds, -1);
	if (access(infile_path, F_OK))
	{
		(*shell_data)->exit_code = 1;
		ft_no_such_file(infile_path);
		return (2);
	}
	else if (access(infile_path, R_OK))
	{
		(*shell_data)->exit_code = 1;
		ft_perm_denied(infile_path);
		return (2);
	}
	return (0);
}
