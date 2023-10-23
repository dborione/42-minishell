/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:48:27 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/23 12:23:00 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static
void	ft_first_command(t_shell_data **shell_data, t_cmd *cmd)
{
	if ((*shell_data)->infile && (*shell_data)->input_fd > -1)
	{
		if (dup2((*shell_data)->input_fd, STDIN_FILENO) == -1)
			return ;
		// if (cmd->next)
		// {
		// 	if (dup2((*shell_data)->pipe[1], STDOUT_FILENO) == -1)
		// 		return ;
		// }
		// //close((*shell_data)->pipe[0]);
		close((*shell_data)->input_fd);
		(*shell_data)->input_fd = -1;
	}
	if (!cmd->next && (*shell_data)->outfile && (*shell_data)->output_fd > -1)
	{
		if (dup2((*shell_data)->output_fd, STDOUT_FILENO) == -1)
			return ;
		// if (dup2((*shell_data)->pipe[0], STDIN_FILENO) == -1)
		// 	return ;
		//close((*shell_data)->pipe[1]);
		close((*shell_data)->output_fd);
		(*shell_data)->output_fd = -1;
	}
	if (cmd->builtin)
	{
		ft_printf("built\n");
		exit(ft_execute_builtin(shell_data, cmd));
	}
	execve(cmd->path, &(cmd)->args[0], (*shell_data)->envp);
	ft_printf("command failed : %s\n", (cmd)->args[0]);
	exit(EXIT_FAILURE);
}

static
void	ft_next_command(t_shell_data **shell_data, t_cmd *cmd)
{
	if (cmd->builtin)
	{
		ft_printf("built\n");
		exit(ft_execute_builtin(shell_data, cmd));
	}
	execve(cmd->path, &(cmd)->args[0], (*shell_data)->envp);
	ft_printf("command failed : %s\n", (cmd)->args[0]);
	exit(EXIT_FAILURE);
}

static
void	ft_next_commands(t_shell_data **shell_data, t_cmd *cmds)
{
	int				parent;
	//int				status;

	if (cmds->next)
	{
		parent = fork();
		if (parent < 0)
			perror("bash");
		if (parent == 0)
			ft_next_command(shell_data, cmds);
		else {
			ft_next_commands(shell_data, cmds->next);
			//waitpid(parent, &status, 0);
		} 
	} else if ((*shell_data)->outfile && (*shell_data)->output_fd > -1) {
		if (dup2((*shell_data)->output_fd, STDOUT_FILENO) == -1)
			return ;
		if (dup2((*shell_data)->pipe[0], STDIN_FILENO) == -1)
			return ;
		//close((*shell_data)->pipe[1]);
		close((*shell_data)->output_fd);
		(*shell_data)->output_fd = -1;
	}
	ft_next_command(shell_data, cmds);
}

static
void	ft_multi_execution(t_shell_data **shell_data, t_cmd *cmds)
{
	int				parent;
	//int				status;

	parent = fork();
	if (parent < 0)
		perror("bash");
	if (parent == 0)
		ft_first_command(shell_data, cmds);
	else
	{
		ft_next_commands(shell_data, cmds->next);
		//waitpid(parent, &status, 0);
		//printf("exit code %d\n", status);
	}
	
}

void	ft_execution(t_shell_data **shell_data, t_cmd *cmds)
{
	if (cmds->next)
	{
		ft_printf("cmd: '%s' args[1]: '%s'\n", cmds->next->name, cmds->next->args[1]);
		ft_multi_execution(shell_data, cmds);
		return ;
	}
	else
	{
		ft_printf("cmd exe: '%s' args[1]: '%s'\n", cmds->name, cmds->args[1]);
		ft_first_command(shell_data, cmds);
	}

	// execve(cmds->path, &(cmds)->args[0], (*shell_data)->envp);
	// ft_printf("command failed : %s\n", (cmds)->args[0]);
	// exit(EXIT_FAILURE);
}

