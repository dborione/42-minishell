/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborione <dborione@student.s19.be>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:16:18 by dborione          #+#    #+#             */
/*   Updated: 2023/09/27 13:16:19 by dborione         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_get_input(t_shell_data **shell_data)
{
	// char    *hist_file;
	char	*line;
	t_args_list	*args;
	t_cmd	*cmds;

	// hist_file = ft_strjoin(ft_envp_get_value((*shell_data)->envp, "HOME"), "/.history");
	using_history();
	stifle_history(1000);
	while (!(*shell_data)->exit)
	{
		(*shell_data)->prompt = ft_show_user_path((*shell_data)->envp);
		line = readline((*shell_data)->prompt);
		free((*shell_data)->prompt);
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				ft_putstr_fd("exit\n", STDOUT_FILENO);
			free(line);
			break;
		};
		args = ft_split_args(shell_data, line);
		if (!args)
		{
			perror("bash");
			free(line);
			break;
		};
		// t_args_list *target_a;
		// target_a = args;
		// ft_printf("¨¨¨\n");
		// while (target_a)
		// {
		// 		printf("separator: %i (%s)\n", target_a->separator, target_a->value);
		// 	target_a = target_a->next;
		// }
		// ft_printf("¨¨¨\n");
		add_history(line);
		if (args->separator && ft_isequal(args->value, "|"))
		{
			ft_wrong_tokens_syntax(shell_data, '|');
			free(line);
			continue ;
		}
		//ft_add_to_history_file(&hist_file, line);
		cmds = ft_parse_input(shell_data, args);
		ft_free_args_list(&args);
		free(line);
		if (!cmds)
		{
			//(*shell_data)->exit_code = 127;
			//ft_printf("!cmds\n");
			continue ;
		}
		// int y = 0;
		// t_cmd *target;
		// target = cmds;
		// ft_printf("¨¨¨\n");
		// while (target)
		// {
		// 	y = 0;
		// 	while (target->args[y])
		// 	{
		// 		printf("id: %zu (%s)\n", target->id, target->args[y]);
		// 		y++;
		// 	}
		// 	target = target->next;
		// }
		// ft_printf("¨¨¨\n");
		ft_execution(shell_data, &cmds);
		ft_free_commands(&cmds);
	}
	clear_history();
	// unlink(hist_file);
	// free(hist_file);
}
