/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:22:45 by dborione          #+#    #+#             */
/*   Updated: 2023/10/24 15:54:04 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_add_token_to_list(t_lexer_tokens **lexer_list, char **input, int token)
{
    t_lexer_tokens	*newnode;
    t_lexer_tokens	*tmp_lexer_list;

	tmp_lexer_list = *lexer_list;
	newnode = malloc(sizeof(t_lexer_tokens));
	if (!newnode)
		return (0);
	newnode->input = *input;
	newnode->token = token;
	newnode->next = NULL;
	if (!*lexer_list)
	{
		*lexer_list = newnode;
		return (1);
	}
	while (tmp_lexer_list)
	{
		if (!tmp_lexer_list->next)
			break;
		tmp_lexer_list = tmp_lexer_list->next;
	}
	tmp_lexer_list->next = newnode;
	return (1);
}
