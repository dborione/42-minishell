/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:52:52 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/18 15:59:55 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_heredoc(char *line)
{
	char *eof;
    char *input;

    input = readline("> ");
    eof = line;
	while (!ft_isequal(eof, input))
		input = readline("> ");
    return (1);
}