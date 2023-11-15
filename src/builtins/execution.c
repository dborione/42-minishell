/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 02:29:28 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/15 22:24:18 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_execute_builtin(t_shell_data **shell_data, t_cmd *cmd, int sub_process)
{
	int	exit_code;

	if (ft_isequal(cmd->name, "echo"))
		exit_code = ft_echo((*shell_data)->envp, cmd);
	else if (ft_isequal(cmd->name, "pwd"))
		exit_code = ft_pwd(*shell_data);
	else if (ft_isequal(cmd->name, "cd"))
		exit_code = ft_cd(shell_data, cmd);
	else if (ft_isequal(cmd->name, "env"))
		exit_code = ft_env((*shell_data)->envp);
	else if (ft_isequal(cmd->name, "exit"))
		exit_code = ft_exit(shell_data, cmd);
	else if (ft_isequal(cmd->name, "export"))
		exit_code = ft_export(shell_data, cmd);
	else if (ft_isequal(cmd->name, "unset"))
		exit_code = ft_unset(shell_data, cmd);	
	else
		exit_code = 127;
	if (sub_process)
		ft_destroy_shell(shell_data);
	return (exit_code);
}
