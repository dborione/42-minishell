/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:42:15 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/02 20:47:20 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_wrong_tokens_syntax(t_shell_data **shell_data, char token)
{
	(*shell_data)->exit_code = 2;
	ft_putstr_fd("bash: syntax error near unexpected token « ", 2);
	ft_putchar_fd(token, 2);
	ft_putendl_fd(" »", 2);
}

void	ft_wrong_redirection_syntax(t_shell_data **shell_data)
{
	(*shell_data)->exit_code = 2;
	ft_putstr_fd("bash: syntax error near unexpected token « newline »", 2);
}
