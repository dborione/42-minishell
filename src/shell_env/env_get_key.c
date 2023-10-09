/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:39:21 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/04 14:26:13 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_envp_get_key(char *input)
{
	size_t	i;
	char	*res;

	i = 0;
	while (input[i] && input[i] != '=')
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (input[i] && input[i] != '=')
	{
		res[i] = input[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
