/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:30:36 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/06 18:03:16 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_envp_set(char **envp, char **input)
{
	size_t	i;
	char	*key;

	key = ft_envp_get_key(*input);
	if (!key)
		return (0);
	i = 0;
	while (envp[i])
	{
		if (ft_startswith(envp[i], key))
		{
			free(envp[i]);
			free(key);
			//ft_printf(">>>> '%s' <<<<\n", *input);
			envp[i] = *input;
			return (1);
		}
		i++;
	}
	free(key);
	return (ft_envp_add(envp, input));
}
