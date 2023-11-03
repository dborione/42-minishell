/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 01:08:16 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/24 15:54:04 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int ft_parse_exit_args(t_cmd *cmd, int error)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (cmd->args[1][0] == '+' || cmd->args[1][0] == '-')
		j++;
	if (cmd->args[1][j] == '-' && !cmd->args[1][2])
		return (0);
	if (!cmd->args[1][j])
		return (1);
	while(cmd->args[1][j] == '0')
		j++;
	while (cmd->args[++i])
	{
		while(cmd->args[i][j])
		{
			//printf("'%c' ", cmd->args[i][j]);
			if (!ft_isdigit(cmd->args[i][j]))
			{
				if (i == 1)
					error = 1;
				break ;
			}
			j++;
		}
		j = 0;
	}
	return (error);
}

static
int ft_exit_num_msg(t_shell_data **shell_data, t_cmd *cmd)
{
	ft_putstr_fd("bash: exit: ", STDERR_FILENO);
	ft_putstr_fd(cmd->args[1], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	(*shell_data)->exit_code = 255;
	return ((*shell_data)->exit_code);
}

int	ft_exit(t_shell_data **shell_data, t_cmd *cmd)
{
	int error;

	error = 0;
	if (!cmd->args[1])
		return (0);
	error = ft_parse_exit_args(cmd, error);
	if (cmd->args[2] && error != 1)
	{
		ft_putendl_fd("bash: exit: too many arguments.", STDERR_FILENO);
		(*shell_data)->exit_code = 1;
		return ((*shell_data)->exit_code);
	}
	if (ft_isequal(cmd->args[1], "") || error == 1)
		return (ft_exit_num_msg(shell_data, cmd));
	if (ft_isequal(cmd->args[1], "-1"))
	{
		(*shell_data)->exit_code = -1;
		return ((*shell_data)->exit_code);
	}
	if (ft_isequal(cmd->args[1], "0"))
	{
		(*shell_data)->exit_code = 0;
		return ((*shell_data)->exit_code);
	}
	if (cmd->args[1][0] != '-' && ft_strlen(cmd->args[1]) == 19 && ft_atoi(&cmd->args[1][18]) > 7)
		return (ft_exit_num_msg(shell_data, cmd));
	if (cmd->args[1][0] == '-')
	{
		if (ft_strlen(cmd->args[1]) == 20 && ft_atoi(&cmd->args[1][19]) > 8)
			return (ft_exit_num_msg(shell_data, cmd));
		if (ft_strlen(cmd->args[1]) > 20)
			return (ft_exit_num_msg(shell_data, cmd));
	}
	if (cmd->args[1][0] != '-' && ft_strlen(cmd->args[1]) > 19)
		return (ft_exit_num_msg(shell_data, cmd));
	(*shell_data)->exit_code = ft_atoi(cmd->args[1]);
	return ((*shell_data)->exit_code);
}
