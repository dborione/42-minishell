/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:16:18 by dborione          #+#    #+#             */
/*   Updated: 2023/11/17 17:27:18 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
char	*ft_get_line(t_shell_data **shell_data)
{
	char	*line;
	char	*prompt;

	prompt = ft_show_user_path((*shell_data)->envp);
	if (!prompt)
	{
		ft_memory_error(shell_data);
		return (NULL);
	}
	line = readline(prompt);
	free(prompt);
	if (!line)
	{
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		free(line);
		return (NULL);
	}
	return (line);
}

static
t_args_list	*ft_get_args(t_shell_data **shell_data, char **line)
{
	t_args_list	*args_list;

	args_list = ft_split_args(shell_data, *line);
	if (!args_list)
	{
		free(*line);
		return (NULL);
	}
	free(*line);
	if (!ft_add_more_inputs(shell_data, &args_list))
	{
		ft_free_args_list(&args_list);
		ft_destroy_shell(shell_data);
		exit(2);
	}
	return (args_list);
}

static
int	ft_get_commands(t_shell_data **shell_data, t_args_list **args)
{
	(*shell_data)->cmds = ft_parse_input(shell_data, *args);
	ft_free_args_list(args);
	if (!*shell_data || !(*shell_data)->cmds)
		return (0);
	return (1);
}

void	ft_get_input(t_shell_data **shell_data)
{
	char		*line;
	t_args_list	*args;

	using_history();
	stifle_history(1000);
	while (ft_check_shell_health(*shell_data) && !(*shell_data)->exit)
	{
		line = ft_get_line(shell_data);
		if (!line)
			break ;
		add_history(line);
		args = ft_get_args(shell_data, &line);
		if (!args)
			continue ;
		if (ft_invalide_start(shell_data, &args))
			continue ;
		if (!ft_get_commands(shell_data, &args))
			continue ;
		ft_execution(shell_data, &(*shell_data)->cmds);
		if (!*shell_data)
			continue ;
		ft_free_commands(&(*shell_data)->cmds);
	}
	clear_history();
}
