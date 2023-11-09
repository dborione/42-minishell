/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:07:55 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/09 14:04:56 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_free_commands(t_cmd **cmds)
{
	t_cmd	*target;

	if (!cmds || !*cmds)
		return ;
	while (*cmds)
	{
		target = (*cmds)->next;
		if ((*cmds)->name)
			free((*cmds)->name);
		if ((*cmds)->path)
			free((*cmds)->path);
		ft_free_split((*cmds)->args);
		free(*cmds);
		*cmds = target;
	}
	*cmds = NULL;
}
