/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_separator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:47:51 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/13 10:59:41 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int	ft_parse_infile(t_shell_data **shell_data, t_cmd **cmds, t_args_list **target)
{
	if (!(*target)->next)
	{
		ft_wrong_redirection_syntax(shell_data);
		*target = (*target)->next;
		return (1);
	}
	if ((*target)->next->separator)
	{
		if (!ft_isequal((*target)->next->value, ">"))
			ft_wrong_tokens_syntax(shell_data, (*target)->next->value);
		*target = (*target)->next->next;
		return (1);
	}
	if (ft_get_infile(shell_data, *cmds, (*target)->next->value) == 2)
	{
		ft_free_commands(cmds);
		return (0);
	}
	*target = (*target)->next->next;
	return (1);
}

static
int	ft_parse_heredoc(t_shell_data **shell_data, t_cmd **cmds, t_args_list **target)
{
	if (!(*target)->next)
	{
		ft_wrong_redirection_syntax(shell_data);
		*target = (*target)->next;
		return (1);
	}
	if ((*target)->next->separator)
	{
		ft_wrong_tokens_syntax(shell_data, (*target)->next->value);
		*target = (*target)->next->next;
		return (1);
	}
	ft_heredoc(*shell_data, (*target)->next->value);
	if ((*shell_data)->exit_code == SIGINT)
	{
		ft_init_shell_sigaction(*shell_data, MAIN);
		ft_putstr_fd("> \n", STDOUT_FILENO);
		ft_free_commands(cmds);
		return (0);
	}
	*target = (*target)->next->next;
	return (1);
}

static
int	ft_parse_outfile(t_shell_data **shell_data, t_cmd **cmds, t_args_list **target, int append)
{
	if (!(*target)->next)
	{
		ft_wrong_redirection_syntax(shell_data);
		*target = (*target)->next;
		return (1);
	}
	if ((*target)->next->separator)
	{
		ft_wrong_tokens_syntax(shell_data, (*target)->next->value);
		*target = (*target)->next->next;
		return (1);
	}
	if (!ft_get_outfile(shell_data, *cmds, (*target)->next->value, append))
	{
		ft_free_commands(cmds);
		return (0);
	}
	(*target) = (*target)->next->next;
	return (1);
}

static
int	ft_parse_command(t_shell_data **shell_data, t_cmd **cmds, t_args_list **target, int *skip)
{
	if (!ft_add_command(cmds, *target, (*shell_data)->paths))
	{
		(*shell_data)->exit_code = 127;
		ft_free_commands(cmds);
		return (0);
	}
	*skip = 1;
	ft_set_command_fds(shell_data, *cmds);
	return (1);
}

int	ft_parse_separator(
	t_shell_data **shell_data, t_cmd **cmds, t_args_list **target, int *skip)
{
	int	res;

	if ((*target)->separator && ft_isequal((*target)->value, "<"))
		res = ft_parse_infile(shell_data, cmds, target);
	else if ((*target)->separator && ft_isequal((*target)->value, "<<"))
		res = ft_parse_heredoc(shell_data, cmds, target);
	else if ((*target)->separator && ft_isequal((*target)->value, ">"))
		res = ft_parse_outfile(shell_data, cmds, target, 0);
	else if ((*target)->separator && ft_isequal((*target)->value, ">>"))
		res = ft_parse_outfile(shell_data, cmds, target, 1);
	else if ((*target)->separator && ft_isequal((*target)->value, "|"))
	{
		res = 1;
		(*shell_data)->pipes++;
		*target = (*target)->next;
		*skip = 0;
	}
	else if (!(*skip))
		res = ft_parse_command(shell_data, cmds, target, skip);
	else
		return (0);
	if (res)
		return (1);
	return (-1);
	// return (res);
}
