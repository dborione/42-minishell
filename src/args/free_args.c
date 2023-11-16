/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:19:18 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/16 10:38:41 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_free_args_list(t_args_list **args)
{
    t_args_list	*target;

    target = *args;
	while (target)
	{
        *args = target->next;
		free(target->value);
        free(target);
        target = *args;
    }
	*args = NULL;
}

void		*ft_exit_split_args(t_data_split **data, t_args_list **args_list)
{
	ft_free_args_list(args_list);
	if (data && *data)
	{
		free((*data)->tmp);
		free(*data);
	}
	return (NULL);
}
