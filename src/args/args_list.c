/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:01:24 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/16 13:29:41 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_args_list	*ft_new_args_list(char *tmp)
{
	t_args_list	*new_arg;

	new_arg = malloc(sizeof(t_args_list));
	if (!new_arg)
		return (NULL);
	new_arg->value = ft_strdup(tmp);
	if (!new_arg->value)
	{
		free(new_arg);
		return (NULL);
	}
	new_arg->separator = 0;
	new_arg->fd = -1;
	new_arg->next = NULL;
	return (new_arg);
}

int	ft_add_arg_to_list(t_args_list **cmd_split, char *tmp)
{
	t_args_list	*target_arg;

	if (!*cmd_split)
	{
		*cmd_split = ft_new_args_list(tmp);
		if (!*cmd_split)
			return (0);
		return (1);
	}
	target_arg = *cmd_split;
	while (target_arg->next)
		target_arg = target_arg->next;
	target_arg->next = ft_new_args_list(tmp);
	if (!target_arg->next)
		return (0);
	return (1);
}

int	ft_join_args(t_args_list **cmd_split, char *tmp)
{
	t_args_list	*target_arg;

	if (!*cmd_split || !tmp)
		return (0);
	target_arg = *cmd_split;
	while (target_arg->next)
		target_arg = target_arg->next;
	target_arg->value = ft_cleanjoin(target_arg->value, tmp);
	if (!target_arg)
		return (0);
	return (1);
}

char	**ft_args_list_to_str_split(t_args_list **cmd_split)
{
	t_args_list	*target;
	size_t		i;
	char		**res;

	target = *cmd_split;
	i = 0;
	while (target)
	{
		target = target->next;
		i++;
	}
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	target = *cmd_split;
	while (target)
	{
		res[i] = target->value;
		target = target->next;
		i++;
	}
	res[i] = NULL;
	i = 0;
	return (res);
}
