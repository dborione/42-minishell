/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:55:01 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/07 00:17:50 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int	ft_use_pipe(t_shell_data **shell_data, t_cmd *cmd, int pipe_fd[2])
// {
// 	if ((*shell_data)->input_fd != STDIN_FILENO)
// 	{
// 		if (dup2((*shell_data)->input_fd, STDIN_FILENO) == -1)
// 			return (0);
// 	}
// 	if (cmd->next)
// 	{
// 		if (dup2(pipe_fd[WRITE_PIPE], STDOUT_FILENO) == -1)
// 			return (0);
// 	}
// 	else if ((*shell_data)->outfile)
// 	{
// 		if (dup2((*shell_data)->output_fd, STDOUT_FILENO) == -1)
// 			return (0);
// 	}
// 	return (1);
// }

int	ft_use_pipe(t_shell_data **shell_data, t_cmd *cmd, int pipe_fd[2])
{
	if (cmd->input_fd != STDIN_FILENO)
	{
		if (dup2(cmd->input_fd, STDIN_FILENO) == -1)
			return (0);
	}
	else if ((*shell_data)->input_fd != STDIN_FILENO)
	{
		if (dup2((*shell_data)->input_fd, STDIN_FILENO) == -1)
			return (0);
	}
	if (cmd->output_fd != STDOUT_FILENO)
	{
		if (dup2(cmd->output_fd, STDOUT_FILENO) == -1)
			return (0);
	} else 
	if (cmd->next)
	{
		if (dup2(pipe_fd[WRITE_PIPE], STDOUT_FILENO) == -1)
			return (0);
	}
	return (1);
}
