/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:57:36 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/16 11:49:22 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int		ft_init_parsing(t_shell_data **shell_data, t_cmd **cmds, int *skip)
{
	(*shell_data)->paths = ft_split(ft_envp_get_value((*shell_data)->envp, "PATH"), ':');
	if (!(*shell_data)->paths)
	{
		(*shell_data)->exit = 1;
		(*shell_data)->exit_code = 127;
		return (0);
	}
	*cmds = NULL;
	(*shell_data)->pipes = 0;
	*skip = 0;
	return (1);
}

static
int		ft_is_empty_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

static
int		ft_something_to_do(t_shell_data *shell_data, t_args_list *args)
{
	t_args_list	*target;

	target = args;
	while (target)
	{
		if (!ft_is_empty_line(target->value))
			return (1);
		if (!target->next && target->separator)
		{
			ft_wrong_redirection_syntax(shell_data);
			return (0);
		}
		target = target->next;
	}
	return (0);
}

t_cmd	*ft_parse_input(t_shell_data **shell_data, t_args_list *args)
{
	t_args_list	*target;
	int			skip;
	t_cmd		*cmds;
	int			res;

	if (!ft_something_to_do(*shell_data, args))
		return (NULL);
	if (!ft_init_parsing(shell_data, &cmds, &skip))
		return (NULL);
    target = args;
	while ((*shell_data)->paths && target)
	{
		res = ft_parse_separator(shell_data, &cmds, &target, &skip);
		if (res == -1)
		{
			(*shell_data)->exit = 1;
			(*shell_data)->exit_code = 127;
			ft_free_split((*shell_data)->paths);
			return (NULL);
		}
		else if (!res)
			target = target->next;
	}
	ft_free_split((*shell_data)->paths);
	return (cmds);
}
