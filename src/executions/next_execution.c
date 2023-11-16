/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:11:01 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/16 11:25:51 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
void	ft_command_error(t_cmd *cmd, int path_error)
{
	if (path_error)
	{
		if (ft_strrchr(cmd->name, '/'))
			ft_no_such_file(cmd->name);
		else
			ft_command_not_found(cmd->name);
	}
	else
	{
		ft_perror("bash: ");
		ft_perror(cmd->name);
		ft_perror(": is a directory\n");
	}
}

static
void	ft_next_command(t_shell_data **shell_data, t_cmd *cmd, int pipe_fd[2])
{
	if (cmd->input_fd == -1 || cmd->output_fd == -1)
		exit((*shell_data)->exit_code);
	if (!ft_use_pipe(shell_data, cmd, pipe_fd))
		exit(EXIT_FAILURE);
	close(pipe_fd[READ_PIPE]);
	if (cmd->builtin)
		exit(ft_execute_builtin(shell_data, cmd, 1));
	if (opendir(cmd->name) && ft_strrchr(cmd->name, '/'))
	{
		ft_command_error(cmd, 0);
		ft_destroy_shell(shell_data);
		exit(126);
	}
	if (!cmd->path)
	{
		ft_command_error(cmd, 1);
		ft_destroy_shell(shell_data);
		exit (127);
	}
	execve(cmd->path, &(cmd)->args[0], (*shell_data)->envp);
	perror((cmd)->args[0]);
	ft_destroy_shell(shell_data);
	exit(EXIT_FAILURE);
}

static
int	ft_init_next_execution(
	t_shell_data **shell_data, pid_t *parent, int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("bash");
		return (0);
	}
	*parent = fork();
	if (*parent < 0)
	{
		close(pipe_fd[READ_PIPE]);
		close(pipe_fd[WRITE_PIPE]);
		ft_memory_error(shell_data);
		return (0);
	}
	return (1);
}

void	ft_next_execution(t_shell_data **shell_data, t_cmd *cmd)
{
	pid_t	parent;
	int		pipe_fd[2];

	if (!ft_init_next_execution(shell_data, &parent, pipe_fd))
		return ;
	else if (parent == 0)
	{
		ft_init_shell_sigaction(*shell_data, HEREDOC_CHILD);
		if (!ft_use_pipe(shell_data, cmd, pipe_fd))
			exit(EXIT_FAILURE);
		ft_next_command(shell_data, cmd, pipe_fd);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		close(pipe_fd[WRITE_PIPE]);
		cmd->pid = parent;
		if ((*shell_data)->input_fd != STDIN_FILENO)
			close((*shell_data)->input_fd);
		if (cmd->next)
			(*shell_data)->input_fd = pipe_fd[READ_PIPE];
		else
			close(pipe_fd[READ_PIPE]);
	}
}
