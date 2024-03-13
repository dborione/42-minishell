/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:00:36 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 08:37:48 by rbarbiot         ###   ########.fr       */
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

static
int	ft_init(
	t_args_list *args, char ***new_args, t_args_list **target, size_t *i)
{
	*new_args = malloc(sizeof(char *) * (ft_args_len(args) + 1));
	if (!(*new_args))
		return (0);
	*i = 0;
	*target = args;
	return (1);
}

static
int	ft_extract_arg(char **new_args, t_args_list **target, size_t *i)
{
	new_args[*i] = ft_strdup((*target)->value);
	if (!new_args[*i])
	{
		ft_free_split(new_args);
		return (0);
	}
	*i += 1;
	*target = (*target)->next;
	return (1);
}

char	**ft_extract_args(t_args_list *args)
{
	char		**new_args;
	t_args_list	*target;
	size_t		i;

	if (!ft_init(args, &new_args, &target, &i))
		return (NULL);
	while (target && !(target->separator && ft_isequal("|", target->value)))
	{
		if (target->separator)
		{
			if (!target->next)
				break ;
			target = target->next->next;
		}
		else
		{
			if (!ft_extract_arg(new_args, &target, &i))
				return (NULL);
		}
	}
	new_args[i] = NULL;
	return (new_args);
}
