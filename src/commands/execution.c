/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:48:27 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/14 19:37:25 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	if (!cmd->path)
	{
		if (ft_strrchr(cmd->name, '/'))
			ft_no_such_file(cmd->name);
		else
			ft_command_not_found(cmd->name);
		exit (127);
	}
	execve(cmd->path, &(cmd)->args[0], (*shell_data)->envp);
	if (!chdir(cmd->path))
	{
		ft_perror("bash: ");
		ft_perror(cmd->path);
		ft_perror(": is a directory\n");
		exit (126);
	}
	perror((cmd)->args[0]);
	ft_destroy_shell(shell_data);
	exit(EXIT_FAILURE);
}

static
void	ft_next_execution(t_shell_data **shell_data, t_cmd *cmd)
{
	pid_t	parent;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		perror("bash");
	parent = fork();
	if (parent < 0)
	{
		close(pipe_fd[READ_PIPE]);
		close(pipe_fd[WRITE_PIPE]);
		ft_memory_error(&(*shell_data));
	}
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

static
void	ft_multi_execution(t_shell_data **shell_data, t_cmd *cmds)
{
	t_cmd	*target;

	target = cmds;
	while (target)
	{
		// if ((*shell_data)->input_fd != STDIN_FILENO)
		// 	close((*shell_data)->input_fd);
		ft_next_execution(shell_data, target);
		target = target->next;
	}
	if ((*shell_data)->input_fd != STDIN_FILENO)
		close((*shell_data)->input_fd);
}

static
void	ft_unic_builtin(t_shell_data **shell_data, t_cmd *cmd)
{
	int	pipe_fd[2];

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (cmd->input_fd != STDIN_FILENO)
	{
		(*shell_data)->infile = 1;
		(*shell_data)->input_fd = dup(STDIN_FILENO);
	}
	if (cmd->output_fd != STDOUT_FILENO)
	{
		(*shell_data)->outfile = 1;
		(*shell_data)->output_fd = dup(STDOUT_FILENO);
	}
	if (!ft_use_pipe(shell_data, cmd, pipe_fd))
		exit(EXIT_FAILURE);
	(*shell_data)->exit_code = ft_execute_builtin(shell_data, cmd, 0);
	if ((*shell_data)->infile)
	{
		if (dup2((*shell_data)->input_fd, STDIN_FILENO) == -1)
			return ;
		close((*shell_data)->input_fd);
	}
	if ((*shell_data)->outfile)
	{
		if (dup2((*shell_data)->output_fd, STDOUT_FILENO) == -1)
			return ;
		close((*shell_data)->output_fd);
	}
}

void	ft_execution(t_shell_data **shell_data, t_cmd **cmds)
{
	t_cmd	*target;

	if (!(*cmds)->next && (*cmds)->builtin)
		ft_unic_builtin(shell_data, *cmds);
	else
	{
		ft_multi_execution(shell_data, *cmds);
		target = *cmds;
		while (target)
		{
			waitpid(target->pid, &(target)->exit_code, 0);
			if (!target->next)
			{
				if (WIFSIGNALED(target->exit_code))
				{
					printf("\n");
					(*shell_data)->exit_code = 130;
				}
				else
					(*shell_data)->exit_code = WEXITSTATUS(target->exit_code);
			}
			target = target->next;
		}
		ft_free_commands(cmds);
	}
	ft_init_shell_sigaction(*shell_data, MAIN);
	ft_reset_fd(shell_data);
}
