/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:34:36 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/06 16:34:36 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd_split	*ft_new_command_arg(char *tmp)
{
	t_cmd_split	*new_arg;

	new_arg = malloc(sizeof(t_cmd_split));
	if (!new_arg)
		return (NULL);
	new_arg->arg = ft_strdup(tmp);
	if (!new_arg->arg)
	{
		free(new_arg);
		return (NULL);
	}
	new_arg->next = NULL;
	return (new_arg);
}

void        ft_free_command_args(t_cmd_split **cmd_split)
{
    t_cmd_split	*target;

    target = *cmd_split;
	while (target)
	{
        *cmd_split = target->next;
        free(target);
        target = *cmd_split;
    }
}

int	ft_add_command_arg(t_cmd_split **cmd_split, char *tmp)
{
	t_cmd_split	*target_arg;

	if (!tmp)
		return (0);
	if (!*cmd_split)
	{
		*cmd_split = ft_new_command_arg(tmp);
		if (!*cmd_split)
			return (0);
		return (1);
	}
	target_arg = *cmd_split;
	while (target_arg->next)
		target_arg = target_arg->next;
	target_arg->next = ft_new_command_arg(tmp);
	if (!target_arg->next)
		return (0);
	return (1);
}
