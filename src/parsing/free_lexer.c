/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:22:36 by dborione          #+#    #+#             */
/*   Updated: 2023/10/24 15:54:04 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_free_lexer_list(t_lexer_tokens **lexer_list)
{
	t_lexer_tokens *target;

	if (lexer_list && *lexer_list)
	{
		while (*lexer_list)
		{
			target = (*lexer_list)->next;
			free((*lexer_list)->input);
			free(*lexer_list);
			*lexer_list = target;
		}
		*lexer_list = NULL;
	}
}
