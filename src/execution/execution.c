/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:48:27 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/04 12:21:13 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_execution(t_shell_data *shell_data, t_cmd *cmd)
{
	//ft_printf("path: %s, args: %s\n", cmd->path, cmd->args[0]);
	execve(cmd->path, &(cmd)->args[0], shell_data->envp);
	ft_printf("exe failed\n");
}