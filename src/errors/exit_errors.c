/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:55:31 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/16 11:58:07 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_exit_num_msg(t_shell_data **shell_data, t_cmd *cmd)
{
	ft_perror("exit\n");
	ft_perror("bash: exit: ");
	ft_perror(cmd->args[1]);
	ft_perror(": numeric argument required\n");
	(*shell_data)->exit = 1;
	(*shell_data)->exit_code = 255;
	return ((*shell_data)->exit_code);
}

int	ft_exit_arg_msg(t_shell_data **shell_data)
{
	(*shell_data)->exit_code = 1;
	ft_perror("exit\n");
	ft_perror("bash: exit: too many arguments\n");
	return ((*shell_data)->exit_code);
}
