/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 01:08:16 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 15:34:48 by dborione         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int	ft_check_special_cases(char *arg, int i)
{
	if (i == 0 && !arg[i + 1])
		return (0);
	if (i == 0 && (arg[i] != '-' && arg[i] != '+'
			&& arg[i] != ' '))
		return (0);
	if (i != 0 && arg[i] != ' ')
		return (0);
	return (1);
}

static 
int	ft_check_if_long(char *arg, unsigned long long res, int i)
{
	if (arg[0] != '-' && res > __LONG_MAX__)
		return (0);
	if (arg[0] == '-' && (ft_strlen(arg) == 20 && ft_atoi(&arg[i - 1]) <= 8))
		return (1);
	if (ft_strlen(arg) >= 20)
	{
		if (arg[0] == '0')
			return (1);
		return (0);
	}
	return (1);
}

static
int	ft_check_if_digit(char *arg)
{
	int					i;
	unsigned long long	res;

	i = -1;
	res = 0;
	if (ft_isequal(arg, "--"))
		return (1);
	while (arg[++i])
	{
		if (!ft_isdigit(arg[i]))
		{
			if (ft_check_special_cases(arg, i))
				return (0);
		}
		if (arg[i] != ' ' && arg[i] != '-' && arg[i] != '+')
		{
			res *= 10;
			res += arg[i] - '0';
		}
	}
	return (ft_check_if_long(arg, res, i));
}

static
int	ft_set_code_and_exit(t_shell_data **shell_data, char *code)
{
	(*shell_data)->exit = 1;
	(*shell_data)->exit_code = ft_atoi(code);
	return ((*shell_data)->exit_code);
}

int	ft_exit(t_shell_data **shell_data, t_cmd *cmd)
{
	int	i;

	i = 1;
	if (ft_isequal("", cmd->args[i]))
		return (ft_exit_num_msg(shell_data, cmd));
	if (!cmd->args[i])
	{
		(*shell_data)->exit = 1;
		return ((*shell_data)->exit_code);
	}
	if (!ft_check_if_digit(cmd->args[i]))
		return (ft_exit_num_msg(shell_data, cmd));
	if (cmd->args[2])
		return (ft_exit_arg_msg(shell_data));
	return (ft_set_code_and_exit(shell_data, cmd->args[i]));
}
