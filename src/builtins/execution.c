/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 02:29:28 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/29 16:21:09 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_execute_builtin(t_shell_data **shell_data, t_cmd *cmd)
{
	if (ft_isequal(cmd->name, "echo"))
		return (ft_echo((*shell_data)->envp, cmd));
	if (ft_isequal(cmd->name, "pwd"))
		return (ft_pwd());
	if (ft_isequal(cmd->name, "cd"))
		return (ft_cd(shell_data, cmd));
	if (ft_isequal(cmd->name, "env"))
		return (ft_env((*shell_data)->envp));
	if (ft_isequal(cmd->name, "exit"))
	{
		int exit = ft_exit(shell_data, cmd);
		//printf("2: exit code: %d\n", exit);
		return (exit);
	}
	if (ft_isequal(cmd->name, "export"))
		return (ft_export((*shell_data)->envp, (*shell_data)->export_envp, cmd));
	if (ft_isequal(cmd->name, "unset"))
		return (ft_unset((*shell_data)->envp, (*shell_data)->export_envp, cmd));	
	return (127);
}