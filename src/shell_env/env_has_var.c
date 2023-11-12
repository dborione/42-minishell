/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_has_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:24:30 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/12 11:29:41 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env_same_key(char *key, char *var)
{
	size_t	i;
	size_t	end;

	i = 0;
	end = ft_strlen(key);
	while (i < end && var[i])
	{
		if (key[i] != var[i])
			return (0);
		i++;
	}
	if (i != end || (var[i] && var[i] != '='))
		return (0);
	//ft_printf("right one key: %s, var: %s\n", key, var);
	return (1);
}

int	ft_env_has(char **envp, char *key)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (ft_env_same_key(key, envp[i]))
			return (1);
		i++;
	}
	return (0);
}
