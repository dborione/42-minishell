/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:48:27 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/22 01:52:25 by rbarbiot         ###   ########.fr       */
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
	//ft_printf("%s\n", cmd->name);
	if (!cmd->next && shell_data->output_fd > -1)
	{
		if (dup2(shell_data->output_fd, STDOUT_FILENO) == -1)
			return ;
		if (dup2(shell_data->pipe[0], STDIN_FILENO) == -1)
			return ;
		//close(shell_data->pipe[1]);
		close(shell_data->output_fd);
	}
	execve(cmd->path, &(cmd)->args[0], shell_data->envp);
	ft_printf("command failed : %s\n", (cmd)->args[0]);
}
