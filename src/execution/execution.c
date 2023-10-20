/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:48:27 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/20 13:54:26 by rbarbiot         ###   ########.fr       */
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
	// if (cmd->next)
	// 	ft_multi_execution(shell_data, cmd);
	execve(cmd->path, &(cmd)->args[0], shell_data->envp);
	ft_printf("exe failed\n");
}