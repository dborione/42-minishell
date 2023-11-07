/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:55:19 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/06 23:17:18 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		ft_add_command(t_cmd **cmds, char **cmd_args, char **paths, size_t end)
{
	t_cmd	*target;

	if (!cmds)
		return (0);
	if (!*cmds)
	{
		*cmds = ft_get_command(cmd_args, paths, end);
		// erreurs de création de commande à prendre en compte
		//ft_printf("first cmd = %s\n", cmd_args[0]);
		if (!*cmds)
			return (0);
	}
	else
	{
		target = (*cmds);
		while (target->next)
			target = target->next;
		target->next = ft_get_command(cmd_args, paths, end);
		if (!target->next)
			return (0);
		target->next->id = target->id + 1;
		// exit 127 : erreurs de création de commande à prendre en compte
		return (1);
	}
	return (1);
}
