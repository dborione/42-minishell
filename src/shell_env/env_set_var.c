/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:30:36 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/13 23:16:37 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_envp_set(t_shell_data **shell_data, char **input)
{
	size_t	i;
	char	*key;

	key = ft_envp_get_key(*input);
	if (!key)
		return (0);
	i = 0;
	while ((*shell_data)->envp[i])
	{
		if (ft_env_same_key(key, (*shell_data)->envp[i]))
		{
			free((*shell_data)->envp[i]);
			free(key);
			(*shell_data)->envp[i] = *input;
			return (1);
		}
		i++;
	}
	free(key);
	ft_envp_add(shell_data, input);
	return (1);
}

int	ft_private_envp_set(t_shell_data **shell_data, char **input)
{
	size_t	i;
	char	*key;

	key = ft_envp_get_key(*input);
	if (!key)
		return (0);
	i = 0;
	while ((*shell_data)->private_envp[i])
	{
		if (ft_env_same_key(key, (*shell_data)->private_envp[i]))
		{
			free((*shell_data)->envp[i]);
			free(key);
			(*shell_data)->private_envp[i] = *input;
			return (1);
		}
		i++;
	}
	free(key);
	ft_private_envp_add(shell_data, input);
	return (1);
}
