/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_separators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:59:03 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 08:37:00 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_speparators(char *input)
{
	return (input[1]
		&& ((input[0] == '<' && input[1] == '<')
			|| (input[0] == '>' && input[1] == '>')));
}

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
