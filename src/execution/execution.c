/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:48:27 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/22 14:11:35 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static
// void	ft_first_command(t_shell_data *t_shell_data, t_cmd *cmd)
// {

// }

// static
// void	ft_next_commands(t_shell_data *t_shell_data, t_cmd *cmds)
// {
// 	int				parent;
// 	int				status;

// 	parent = fork();
// 	if (parent < 0)
// 		perror("bash");
// 	if (parent == 0)
// 		ft_next_commands(shell_data, cmds);
// 	else
// 	{
// 		ft_next_commands(shell_data, cmds->next);
// 		waitpid(parent, &status, 0);
// 		//printf("exit code %d\n", status);
// 	}
// }

// static
// void	ft_multi_execution(t_shell_data *shell_data, t_cmd *cmds)
// {
// 	int				parent;
// 	int				status;

// 	parent = fork();
// 	if (parent < 0)
// 		perror("bash");
// 	if (parent == 0)
// 		ft_next_commands(shell_data, cmds);
// 	else
// 	{
// 		ft_next_commands(shell_data, cmds->next);
// 		waitpid(parent, &status, 0);
// 		//printf("exit code %d\n", status);
// 	}
	
// }

void	ft_execution(t_shell_data *shell_data, t_cmd *cmd)
{
	//ft_printf("cmd: '%s' args[1]: '%s'\n", cmd->name, cmd->args[1]);
	if (shell_data->infile && shell_data->input_fd > -1)
	{
		if (dup2(shell_data->input_fd, STDIN_FILENO) == -1)
			return ;
		if (cmd->next)
		{
			if (dup2(shell_data->pipe[1], STDOUT_FILENO) == -1)
				return ;
		}
		//close(shell_data->pipe[0]);
		close(shell_data->input_fd);
		shell_data->input_fd = -1;
	}
	if (!cmd->next && shell_data->outfile && shell_data->output_fd > -1)
	{
		if (dup2(shell_data->output_fd, STDOUT_FILENO) == -1)
			return ;
		if (dup2(shell_data->pipe[0], STDIN_FILENO) == -1)
			return ;
		//close(shell_data->pipe[1]);
		close(shell_data->output_fd);
		shell_data->output_fd = -1;
	}
	execve(cmd->path, &(cmd)->args[0], shell_data->envp);
	ft_printf("command failed : %s\n", (cmd)->args[0]);
	exit(EXIT_FAILURE);
}
