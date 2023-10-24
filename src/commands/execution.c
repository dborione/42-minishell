/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:48:27 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/24 14:15:31 by rbarbiot         ###   ########.fr       */
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
		close((*shell_data)->input_fd);
		(*shell_data)->input_fd = -1;
	}
	if (!cmd->next && (*shell_data)->outfile && (*shell_data)->output_fd > -1)
	{
		if (dup2((*shell_data)->output_fd, STDOUT_FILENO) == -1)
			return ;
		close((*shell_data)->output_fd);
		(*shell_data)->output_fd = -1;
	}
	if (cmd->next)
	{
		if (dup2((*shell_data)->pipe[1], STDOUT_FILENO) == -1)
			return ;
		close((*shell_data)->pipe[0]);
	}
	if (cmd->builtin)
		exit(ft_execute_builtin(shell_data, cmd));
	execve(cmd->path, &(cmd)->args[0], (*shell_data)->envp);
	ft_printf("command failed : %s\n", (cmd)->args[0]); //recuperer error code
	exit(EXIT_FAILURE);
}

static
void	ft_next_command(t_shell_data **shell_data, t_cmd *cmd)
{
	ft_printf("%d\n", cmd->id);
	if (cmd->id % 2)
	{
		close((*shell_data)->pipe[1]);
		if (dup2((*shell_data)->pipe[0], STDIN_FILENO) == -1)
			return ;
		close((*shell_data)->swap[0]);
		if (cmd->next)
		{
			if (dup2((*shell_data)->swap[1], STDOUT_FILENO) == -1)
				return ;
		}
		else
			close((*shell_data)->swap[1]);
	}
	else if (cmd->id % 3)
	{
		if (dup2((*shell_data)->swap[0], STDIN_FILENO) == -1)
			return ;
		if (cmd->next)
		{
			if (dup2((*shell_data)->pipe[1], STDOUT_FILENO) == -1)
				return ;
		}
		else
			close((*shell_data)->pipe[1]);
		close((*shell_data)->swap[1]);
		close((*shell_data)->pipe[0]);
	}
	else
	{
		ft_printf("3 >> %d\n", cmd->id);
		close((*shell_data)->swap[1]);
		if (dup2((*shell_data)->swap[0], STDIN_FILENO) == -1)
			return ;
		if (cmd->next)
		{
			if (dup2((*shell_data)->pipe[1], STDOUT_FILENO) == -1)
				return ;
		}
		else
			close((*shell_data)->pipe[1]);
		close((*shell_data)->pipe[0]);
	}
	if (cmd->builtin)
		exit(ft_execute_builtin(shell_data, cmd));
	execve(cmd->path, &(cmd)->args[0], (*shell_data)->envp);
	ft_printf("command failed : %s\n", (cmd)->args[0]);
	exit(EXIT_FAILURE);
}

// static
// void	ft_next_commands(t_shell_data **shell_data, t_cmd *cmds)
// {
// 	pid_t	parent;
// 	//int				status;

// 	if (cmds->next)
// 	{
// 		parent = fork();
// 		if (parent < 0)
// 			perror("bash");
// 		if (parent == 0)
// 			ft_next_command(shell_data, cmds);
// 		else {
// 			// if (dup2((*shell_data)->pipe[0], STDIN_FILENO) == -1)
// 			// 	return ;
// 			// close((*shell_data)->pipe[1]);
// 			// (*shell_data)->input_fd = -1;
// 			//waitpid(-1, NULL, 0);
// 			ft_next_commands(shell_data, cmds->next);
// 		} 
// 	} else if ((*shell_data)->outfile && (*shell_data)->output_fd > -1) {
// 		if (dup2((*shell_data)->output_fd, STDOUT_FILENO) == -1)
// 			return ;
// 		close((*shell_data)->output_fd);
// 		(*shell_data)->output_fd = -1;
// 	}
// 	ft_next_command(shell_data, cmds);
// }

static
void	ft_multi_execution(t_shell_data **shell_data, t_cmd *cmds)
{
	pid_t	parent;
	t_cmd	*target;

	if (pipe((*shell_data)->pipe) == -1 || pipe((*shell_data)->swap) == -1)
		perror("bash");

	// parent = fork();
	// if (parent < 0)
	// 	perror("bash");
	// if (parent == 0)
	// 	ft_first_command(shell_data, cmds);
	// else
	// {
	// 	//waitpid(-1, NULL, 0);
	// 	ft_next_commands(shell_data, cmds->next);
	// 	//waitpid(parent, &status, 0);
	// 	//printf("exit code %d\n", status);
	// }
	//ft_first_command(shell_data, cmds);
	target = cmds;
	while (target)
	{
		parent = fork();
		if (parent < 0)
			perror("bash");
		if (parent == 0)
		{
			if (target->id == 0)
				ft_first_command(shell_data, target);
			else
				ft_next_command(shell_data, target);//ft_first_command(shell_data, cmds);
		}
		else
		{
			target = target->next;
			//waitpid(-1, NULL, 0);
			//ft_next_commands(shell_data, cmds->next);
			//waitpid(parent, &status, 0);
			//printf("exit code %d\n", status);
		}
	}
	waitpid(-1, NULL, 0);
	exit(EXIT_SUCCESS);
}

void	ft_execution(t_shell_data **shell_data, t_cmd *cmds)
{
	if (cmds->next)
	{
		//ft_printf("cmd: '%s' args[1]: '%s'\n", cmds->next->name, cmds->next->args[1]);
		ft_multi_execution(shell_data, cmds);
		return ;
	}
	else
	{
		//ft_printf("cmd exe: '%s' args[1]: '%s'\n", cmds->name, cmds->args[1]);
		ft_first_command(shell_data, cmds);
	}

	// execve(cmds->path, &(cmds)->args[0], (*shell_data)->envp);
	// ft_printf("command failed : %s\n", (cmds)->args[0]);
	// exit(EXIT_FAILURE);
}

