/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:48:27 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/16 11:35:43 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	if ((*shell_data)->input_fd != STDIN_FILENO)
		close((*shell_data)->input_fd);
}

static
void	ft_reset_unic_builtin_fds(t_shell_data **shell_data)
{
	if ((*shell_data)->infile)
	{
		if (dup2((*shell_data)->input_fd, STDIN_FILENO) == -1)
			ft_dup2_error(&(*shell_data), FALSE);
		close((*shell_data)->input_fd);
	}
	if ((*shell_data)->outfile)
	{
		if (dup2((*shell_data)->output_fd, STDOUT_FILENO) == -1)
			ft_dup2_error(&(*shell_data), FALSE);
		close((*shell_data)->output_fd);
	}
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
	ft_reset_unic_builtin_fds(shell_data);
}

static
void	ft_wifsignaled(t_shell_data *shell_data)
{
	ft_printf("\n");
	shell_data->exit_code = 130;
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
					ft_wifsignaled(*shell_data);
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
