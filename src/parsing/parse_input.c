/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:57:36 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/12 22:16:13 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int		ft_init_parsing(t_shell_data **shell_data, t_cmd **cmds, int *skip)
{
	(*shell_data)->paths = ft_split(ft_envp_get_value((*shell_data)->envp, "PATH"), ':');
	if (!(*shell_data)->paths)
		return (0);
	*cmds = NULL;
	(*shell_data)->pipes = 0;
	*skip = 0;
	return (1);
}

t_cmd	*ft_parse_input(t_shell_data **shell_data, t_args_list *args)
{
	t_args_list	*target;
	int			skip;
	t_cmd		*cmds;
	int			res;

	if (!ft_init_parsing(shell_data, &cmds, &skip))
		return (NULL);
    target = args;
	while ((*shell_data)->paths && target)
	{
		res = ft_parse_separator(shell_data, &cmds, &target, &skip);
		if (res == -1)
		{
			ft_free_split((*shell_data)->paths);
			return (NULL);
		}
		else if (!res)
			target = target->next;
	}
	ft_free_split((*shell_data)->paths);
	//(*shell_data)->exit_code = 127;
	return (cmds);
}
