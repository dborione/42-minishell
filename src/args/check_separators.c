/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_separators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:59:03 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/16 11:49:01 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_speparators(char *input, size_t i)
{
	return (input[i + 1]
		&& ((input[i] == '<' && input[i + 1] == '<')
		||  (input[i] == '>' && input[i + 1] == '>')));
}

//int	ft_is_separators_with_fd()

int	ft_is_invalid_args_separator(t_shell_data **shell_data, char *input)
{
	if (ft_startswith(input, "||"))
		ft_wrong_tokens_syntax(shell_data, "||");
	else if (ft_startswith(input, "<<<"))
		ft_wrong_tokens_syntax(shell_data, "<");
	else if (ft_startswith(input, ">>>"))
		ft_wrong_tokens_syntax(shell_data, ">");
	else
		return (0);
	return (1);
}
