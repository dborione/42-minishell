/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 23:48:49 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/06 15:59:49 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static
size_t	ft_quoteslen(char *str, char quote)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != quote)
		len++;
	return (len);
}

char	*ft_get_with_quotes(char *str)
{
	char	quote;
	size_t	i;
	char	*res;

	quote = str[0];
	i = 0;
	res = malloc(sizeof(char) * (ft_quoteslen(str, quote) + 1));
	if (!res)
		return (NULL);
	while (str[i])
	{
		res[i] = str[i];
		if (i > 0 && str[i] == quote)
		{
			i++;
			break ;
		}
		i++;
	}
	res[i] = '\0';
	return (res);
}

int		ft_has_endof_quotes(char *input, char quote)
{
	size_t	i;

	i = 1;
	while (input[i])
	{
		if (input[i] == quote)
			return (1);
		i++;
	}
	return (0);
}
