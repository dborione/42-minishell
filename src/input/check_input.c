/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:57:53 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 17:05:35 by dborione         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_ends_with_pipe(t_args_list *args)
{
	t_args_list	*target;

	target = args;
	while (target->next)
		target = target->next;
	return (target->separator && ft_isequal(target->value, "|"));
}

static
int	ft_has_wrong_separators(t_shell_data **shell_data, t_args_list *args)
{
	t_args_list	*target;

	target = args;
	while (target->next)
	{
		if (target->separator && target->next->separator
			&& !ft_isequal(target->value, "|") 
			&& ft_isequal(target->next->value, "|"))
		{
			ft_wrong_tokens_syntax(shell_data, target->next->value);
			return (1);
		}
		target = target->next;
	}
	return (0);
}

int	ft_invalide_start(
	t_shell_data **shell_data, t_args_list **args)
{
	t_args_list	*target;

	if ((*args)->separator && ft_isequal((*args)->value, "|"))
	{
		ft_wrong_tokens_syntax(shell_data, "|");
		ft_free_args_list(args);
		return (1);
	}
	if (ft_has_wrong_separators(shell_data, *args))
	{
		ft_free_args_list(args);
		return (1);
	}
	target = *args;
	while (target->next)
		target = target->next;
	if (target->separator && !ft_isequal(target->value, "|"))
	{
		ft_wrong_redirection_syntax(*shell_data);
		ft_free_args_list(args);
		return (1);
	}
	return (0);
}
