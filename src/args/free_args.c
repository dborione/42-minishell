/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:19:18 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/22 14:21:12 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_args_list(t_args_list **cmd_split)
{
    t_args_list	*target;

    target = *cmd_split;
	while (target)
	{
        *cmd_split = target->next;
        free(target);
        target = *cmd_split;
    }
}
