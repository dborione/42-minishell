/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:00:36 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/02 23:18:17 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_extract_args(char **args, size_t end)
{
	size_t	i;
	char	**new_args;

	new_args = malloc(sizeof(char *) * (end + 1));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < end)
	{
		//ft_printf("this: %s\n", args[i]);
		new_args[i] = ft_strdup(args[i]);
		if (!new_args[i])
		{
			ft_free_split(new_args);
			return (NULL);
		}
		i++;
	}
	new_args[i] = NULL;
	//ft_printf("first arg = %s\n", args[0]);
	return (new_args);
}
