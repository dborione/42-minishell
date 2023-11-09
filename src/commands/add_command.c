/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:55:19 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/09 11:34:36 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

size_t	ft_add_command(t_cmd **cmds, t_args_list *args, char **paths)
{
	t_cmd	*target;

	if (!cmds)
		return (0);
	if (!*cmds)
	{
		*cmds = ft_get_command(args, paths);
		// erreurs de création de commande à prendre en compte
		if (!*cmds)
			return (0);
		return (1);
	}
	target = (*cmds);
	while (target->next)
		target = target->next;
	target->next = ft_get_command(args, paths);
	if (!target->next)
		return (0);
	target->next->id = target->id + 1;
	// exit 127 : erreurs de création de commande à prendre en compte
	return (1);
}
