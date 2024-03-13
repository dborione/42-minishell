/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:09:37 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 17:55:30 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static
// void	*ft_handle_sigint_pipe(t_args_list **args_list, char *line)
// {
// 	int	i;
// 	int	*res;

// 	i = 1;
// 	res = &i;
// 	// kill(1, SIGINT);
// 	printf("jfdkls\n");
// 	return (res);
// 	ft_free_args_list(args_list);
// 	if (line)
// 		free(line);
// }

static
int	ft_add_input(t_shell_data **shell_data, 
		t_args_list **args_list, char *line)
{
	t_args_list	*target;

	target = *args_list;
	while (target->next)
		target = target->next;
	target->next = ft_split_args(shell_data, line);
	if (!target->next)
		return (0);
	return (1);
}

static
int	ft_add_input_crash(t_args_list **args_list, char *line)
{
	if (line)
		free(line);
	ft_free_args_list(args_list);
	return (0);
}

int	ft_add_more_inputs(t_shell_data **shell_data, t_args_list **args_list)
{
	char	*line;

	while (ft_ends_with_pipe(*args_list))
	{
		if (ft_invalide_start(shell_data, args_list))
			return (1);
		line = readline("> ");
		if (!line)
			return (0);
		if (ft_is_empty_line(line))
		{
			free(line);
			continue ;
		}
		if (!line)
			return (ft_add_input_crash(args_list, NULL));
		if (!ft_add_input(shell_data, args_list, line))
			return (ft_add_input_crash(args_list, line));
		free(line);
	}
	return (1);
}
