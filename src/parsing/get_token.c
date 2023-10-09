/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:22:45 by dborione          #+#    #+#             */
/*   Updated: 2023/10/03 16:04:27 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_get_token_from_input(char *input)
{
    int i;
    size_t len;

    len = ft_strlen(input);
    if ((input[0] == '|' || input[0] == '<' || input[0] == '>') && len == 1)
        return (SYMBOL);
    i = -1;
    while (input[++i])
    {
        if (input[i] == '$' && len > 1)
            return (ENV_VAR);
    }
    i = -1;
    while (input[++i])
    {
        if (ft_isalpha(input[i]))
            return (CMD); // pas bon, les commandes peuvent contenir des caracters non alphabetiques
    }
    return (CMD);
}
