/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:16:18 by dborione          #+#    #+#             */
/*   Updated: 2023/11/09 13:49:36 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
char		*ft_get_line(t_shell_data **shell_data) // define exit_code
{
	char	*line;
	char	*prompt;

	prompt = ft_show_user_path((*shell_data)->envp);
	if (!prompt)
	{
		perror("bash");
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
	t_args_list	*args;

	if	(!line || !*line)
		return (NULL);
	args = ft_split_args(shell_data, *line);
	if (!args)
	{
		//perror("bash");
		free(*line);
		return (NULL);
	};
	return (args);
}

static
int			ft_invalide_start(t_shell_data **shell_data, t_args_list **args, char **line)
{
	if ((*args)->separator && ft_isequal((*args)->value, "|"))
	{
		ft_wrong_tokens_syntax(shell_data, '|');
		free(*line);
		ft_free_args_list(args);
		return (1);
	}
	return (0);
}

void	test_print_args(t_args_list *args)
{
	t_args_list *target_a;
	target_a = args;
	ft_printf("¨¨¨\n");
	while (target_a)
	{
			printf("separator: %i (%s)\n", target_a->separator, target_a->value);
		target_a = target_a->next;
	}
	ft_printf("¨¨¨\n");
}

void	test_print_cmds(t_cmd *cmds)
{
	int y = 0;
	t_cmd *target;

	target = cmds;
	ft_printf("¨¨¨\n");
	while (target)
	{
		y = 0;
		while (target->args[y])
		{
			printf("id: %zu (%s)\n", target->id, target->args[y]);
			y++;
		}
		target = target->next;
	}
	ft_printf("¨¨¨\n");
}

void ft_get_input(t_shell_data **shell_data)
{
	char	*line;
	t_args_list	*args;
	t_cmd	*cmds;

	using_history();
	stifle_history(1000);
	while (!(*shell_data)->exit)
	{
		line = ft_get_line(shell_data);
		if (!line)
			break;
		args = ft_get_args(shell_data, &line);
		if (!args)
			continue; // a voir
		add_history(line);
		if (ft_invalide_start(shell_data, &args, &line))
			continue;
		cmds = ft_parse_input(shell_data, args);
		ft_free_args_list(&args);
		free(line);
		if (!cmds) // define exit_code
			continue ;
		ft_execution(shell_data, &cmds);
		ft_free_commands(&cmds);
	}
	clear_history();
}
