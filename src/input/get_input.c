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
	//char    *hist_file;
	char 			*line;
	t_lexer_tokens 	*lexer_list;
	char			**input;

	//hist_file = ft_strjoin(ft_envp_get_value((*shell_data)->envp, "HOME"), "/.history");
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
			break ;
		};
		ft_printf("---\n");
		int	y = 0;
		while (input[y])
		{
			ft_printf("(%s)\n", input[y]);
			y++;
		}
		ft_printf("---\n");
		add_history(line);
		//ft_add_to_history_file(&hist_file, line);
		lexer_list = ft_parse_input(shell_data, line);
		free(line);
		if (!lexer_list)
			continue;
		ft_parse_elements(shell_data, &lexer_list);
		ft_free_lexer_list(&lexer_list);
	}
	clear_history();
	// unlink(hist_file);
	// free(hist_file);
}
