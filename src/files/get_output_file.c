/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_output_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:47:14 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 17:13:03 by dborione         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int	ft_is_dir(char *path)
{
	void	*fd;

	fd = opendir(path);
	if (fd)
	{
		closedir(fd);
		return (1);
	}
	if (errno == ENOTDIR)
		return (0);
	return (1);
}

static
void	ft_command_error(char *name)
{
	ft_perror("bash: ");
	ft_perror(name);
	ft_perror(": is a directory\n");
}

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

static
int	ft_fd_failure(t_shell_data **shell_data,
	char *outfile_path, int exit_code)
{
	if (exit_code)
		(*shell_data)->exit_code = exit_code;
	else
		(*shell_data)->exit_code = EXIT_FAILURE;
	if (ft_is_dir(outfile_path))
		ft_command_error(outfile_path);
	else
		ft_perm_denied(outfile_path);
	return (0);
}

int	ft_get_outfile(t_shell_data **shell_data, 
		t_cmd *cmds, char *outfile_path, int append)
{
	int	fd;
	int	exit_code;

	exit_code = 0;
	if (outfile_path && append)
		fd = open(outfile_path, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (outfile_path)
		fd = open(outfile_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
	{
		ft_wrong_redirection_syntax(*shell_data);
		fd = -1;
		exit_code = 2;
	}
	ft_set_cmd_outfile_fd(shell_data, cmds, fd);
	if (fd == -1)
		return (ft_fd_failure(shell_data, outfile_path, exit_code));
	return (1);
}
