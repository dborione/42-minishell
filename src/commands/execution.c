/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:48:27 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/06 23:49:00 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
void	ft_next_command(t_shell_data **shell_data, t_cmd *cmd, int pipe_fd[2])
{
	if (cmd->input_fd == -1)
		exit(1);
	if (!ft_use_pipe(shell_data, cmd, pipe_fd))
		exit(EXIT_FAILURE);
	close(pipe_fd[READ_PIPE]);
	if (cmd->builtin)	// s'occuper des frees ?
		exit(ft_execute_builtin(shell_data, cmd));
	if (!cmd->path)
	{
		ft_command_not_found(cmd->name);
		(*shell_data)->exit_code = 127;
		exit((*shell_data)->exit_code);
	}
	execve(cmd->path, &(cmd)->args[0], (*shell_data)->envp);
	//ft_printf("command failed : %s\n", (cmd)->args[0]);
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
		perror("bash");
	}
	else if (parent == 0)
		ft_next_command(shell_data, cmd, pipe_fd);
	else
	{
		close(pipe_fd[WRITE_PIPE]);
		if (cmd->next)
			(*shell_data)->input_fd = pipe_fd[READ_PIPE];
		// else
		// {
		// 	close(pipe_fd[READ_PIPE]);
		// 	if ((*shell_data)->outfile)
		// 		close((*shell_data)->output_fd);
		// }
	}
}

static
void	ft_multi_execution(t_shell_data **shell_data, t_cmd *cmds)
{
	t_cmd	*target;

	target = cmds;
	while (target)
	{
		ft_next_execution(shell_data, target);
		target = target->next;
	}
}

void	ft_execution(t_shell_data **shell_data, t_cmd **cmds)
{
	t_cmd	*target;

	if (!(*cmds)->next && (*cmds)->builtin)
		(*shell_data)->exit_code = ft_execute_builtin(shell_data, *cmds);
	else
	{
		ft_multi_execution(shell_data, *cmds);
		target = *cmds;
		while (target)
		{
			signal(SIGINT, SIG_IGN);
			waitpid(-1, &(*shell_data)->exit_code, 0);
    		(*shell_data)->exit_code = WEXITSTATUS((*shell_data)->exit_code);
			target = target->next;
		}
		// if ((*shell_data)->infile)
		// 	close((*shell_data)->input_fd);
		// if ((*shell_data)->outfile)
		// 	close((*shell_data)->output_fd);
		(*shell_data)->infile = 0;
		(*shell_data)->outfile = 0;
		if ((*shell_data)->exit_code == 2) // pour cat SIGINT
			ft_putstr_fd("\n", STDOUT_FILENO);
		ft_init_shell_sigaction(*shell_data, MAIN);
		ft_free_commands(cmds);
	}
}

