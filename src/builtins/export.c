/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:42:06 by dborione          #+#    #+#             */
/*   Updated: 2023/11/17 18:38:28 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int	ft_check_valid_char(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i++;
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] != '=' )
			return (0);
		if (!ft_isalnum(arg[i]))
		{
			if (arg[i] == '=' || arg[i] == '_')
			{
				if (ft_isalnum(arg[i - 1])
					|| arg[i - 1] == '+' || arg[i - 1] == '_')
					return (1);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

static
int	ft_redifine(char *var)
{
	size_t	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static
int	ft_export_set_var(t_shell_data **shell_data, t_cmd *cmd, size_t i)
{
	if (!ft_check_valid_char(cmd->args[i]))
	{
		ft_export_error(cmd->args[i++]);
		if (!cmd->args[i])
			return (1);
	}
	if (!ft_env_has((*shell_data)->private_envp, cmd->args[i]) 
		|| ft_redifine(cmd->args[i]))
	{
		if (!ft_private_envp_set(shell_data, cmd->args[i]))
			return (127);
		if (ft_redifine(cmd->args[i]) && !ft_envp_set(shell_data, cmd->args[i]))
			return (127);
	}
	return (0);
}

int	ft_export(t_shell_data **shell_data, t_cmd *cmd)
{
	int	i;
	int	exit_code;

	i = 1;
	if (!cmd->args[1])
		return (ft_export_env(shell_data));
	while (cmd->args[i])
	{
		exit_code = ft_export_set_var(shell_data, cmd, i);
		if (exit_code)
			return (exit_code);
		i++;
	}
	return (0);
}
