/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 01:08:16 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/23 12:09:08 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(t_shell_data **shell_data, t_cmd *cmd)
{
	if (cmd->args[1])
	{
		ft_putendl_fd("bash: exit: too many arguments.", 2);
		return (0);
	}
	(*shell_data)->exit = 1;
	return (1);
}