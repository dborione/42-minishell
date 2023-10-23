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

#include "../minishell.h"

void ft_free_lst(t_lexer_tokens *lexer_lst)
{
	t_lexer_tokens *tmp_lexer_lst;

	tmp_lexer_lst = lexer_lst;
	while (lexer_lst)
	{
		tmp_lexer_lst = lexer_lst;
		lexer_lst = lexer_lst->next;
		free(tmp_lexer_lst);
	}
}

void ft_get_input(t_shell_data **shell_data)
{
	char    *hist_file;
	char 			*line;
	t_lexer_tokens 	*lexer_list;

	hist_file = ft_strjoin(ft_envp_get_value((*shell_data)->envp, "HOME"), "/.history");
	while (!(*shell_data)->exit)
	{
		using_history();
		stifle_history(1000);
		line = readline(ft_show_user_path((*shell_data)->envp));
		ft_add_to_history_file(*shell_data, &hist_file, line);
		if (!line || !line[0])
			continue;

		lexer_list = ft_parse_input(shell_data, line);
		if (!lexer_list)
		{
			perror("bash");
			break;
		}
		ft_parse_elements(shell_data, &lexer_list);
		free(line);
	}
	// free(line); pour le break
	unlink(hist_file);
}
