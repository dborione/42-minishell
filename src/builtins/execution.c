/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 02:29:28 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/23 12:01:07 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execute_builtin(t_shell_data **shell_data, t_cmd *cmd)
{
	ft_printf("lets builtin\n");
	if (ft_isequal(cmd->name, "echo"))
		return (ft_echo((*shell_data)->envp, cmd));
	if (ft_isequal(cmd->name, "pwd"))
		return (ft_pwd((*shell_data)->envp));
	if (ft_isequal(cmd->name, "cd"))
		return (ft_cd(shell_data, cmd));
	if (ft_isequal(cmd->name, "env"))
		return (ft_env((*shell_data)->envp));
	if (ft_isequal(cmd->name, "exit"))
		return (ft_exit(shell_data, cmd));	
}