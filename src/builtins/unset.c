/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborione <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:35:47 by dborione          #+#    #+#             */
/*   Updated: 2023/11/17 15:42:00 by dborione         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int	ft_check_valid_char(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[0]))
		return (0);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]))
		{
			if (arg[i] == '=' || arg[i] == '_')
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_unset(t_shell_data **shell_data, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[++i])
	{
		if (!ft_check_valid_char(cmd->args[i]))
		{
			ft_export_error(cmd->args[i]);
			++i;
			if (!cmd->args[i])
				break ;
		}
		if (ft_env_has((*shell_data)->envp, cmd->args[i]))
		{
			if (!ft_envp_unset(shell_data, cmd->args[i]))
				return (1);
		}
	}
	return (0);
}
