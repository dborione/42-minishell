/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:30:36 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 16:46:05 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int	ft_var_set(t_shell_data **shell_data, char *input, size_t i)
{
	char	*var_copy;

	var_copy = ft_strdup((*shell_data)->envp[i]);
	if (!var_copy)
		return (0);
	free((*shell_data)->envp[i]);
	(*shell_data)->envp[i] = ft_var_new_value(input, var_copy);
	if (!(*shell_data)->envp[i])
	{
		(*shell_data)->envp[i] = var_copy;
		return (0);
	}
	free(var_copy);
	return (1);
}

int	ft_envp_set(t_shell_data **shell_data, char *input)
{
	size_t	i;
	char	*key;

	key = ft_envp_get_key(input);
	if (!key)
		return (0);
	i = 0;
	while ((*shell_data)->envp[i])
	{
		if (ft_env_same_key(key, (*shell_data)->envp[i]))
		{
			free(key);
			return (ft_var_set(shell_data, input, i));
		}
		i++;
	}
	free(key);
	return (ft_envp_add(shell_data, input));
}

static
int	ft_private_var_set(t_shell_data **shell_data, char *input, size_t i)
{
	char	*var_copy;

	var_copy = ft_strdup((*shell_data)->private_envp[i]);
	if (!var_copy)
		return (0);
	free((*shell_data)->private_envp[i]);
	(*shell_data)->private_envp[i] = ft_var_new_value(input, var_copy);
	if (!(*shell_data)->private_envp[i])
	{
		(*shell_data)->private_envp[i] = var_copy;
		return (0);
	}
	free(var_copy);
	return (1);
}

int	ft_private_envp_set(t_shell_data **shell_data, char *input)
{
	size_t	i;
	char	*key;

	key = ft_envp_get_key(input);
	if (!key)
		return (0);
	i = 0;
	while ((*shell_data)->private_envp[i])
	{
		if (ft_env_same_key(key, (*shell_data)->private_envp[i]))
		{
			free(key);
			return (ft_private_var_set(shell_data, input, i));
		}
		i++;
	}
	free(key);
	return (ft_private_envp_add(shell_data, input));
}
