/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:01:24 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/22 15:01:40 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_args_list	*ft_new_args_list(char *tmp)
{
	t_args_list	*new_arg;

	new_arg = malloc(sizeof(t_args_list));
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