/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:42:15 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/16 11:57:53 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_wrong_tokens_syntax(t_shell_data **shell_data, char *token)
{
	char	*tmp;
	char	*message;

	(*shell_data)->exit_code = 2;
	tmp = ft_strjoin(token, " »\n");
	if (!tmp)
	{
		(*shell_data)->exit_code = 127;
		return ;
	}
	message = ft_strjoin("bash: syntax error near unexpected token « ", tmp);
	free(tmp);
	if (!message)
	{
		(*shell_data)->exit_code = 127;
		return ;
	}
	if (!ft_perror(message))
		(*shell_data)->exit_code = 127;
	free(message);
}

void	ft_wrong_redirection_syntax(t_shell_data *shell_data)
{
	shell_data->exit_code = 2;
	ft_putstr_fd("bash: syntax error near unexpected token « newline »\n", 2);
}
