/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:00:36 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/09 11:44:44 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
size_t	ft_args_len(t_args_list *args)
{
	t_args_list	*target;
	size_t		len;

	target = args;
	len = 0;
	while (target && !(target->separator && ft_isequal("|", target->value)))
	{
		if (target->separator)
		{
			if (!target->next)
				return (len);
			target = target->next->next;
		}
		else
		{
			len++;
			target = target->next;
		}
	}
	return (len);
}

char	**ft_extract_args(t_args_list *args)
{
	char		**new_args;
	t_args_list	*target;
	size_t		i;

	new_args = malloc(sizeof(char *) * (ft_args_len(args) + 1));
	if (!new_args)
		return (NULL);
	i = 0;
	target = args;
	while (target && !(target->separator && ft_isequal("|", target->value)))
	{
		if (target->separator)
		{
			if (!target->next)
				break;
			target = target->next->next;
		}
		else
		{
			new_args[i++] = ft_strdup(target->value);
			target = target->next;
		}
	}
	new_args[i] = NULL;
	return (new_args);
}
