/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:30:36 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/11 01:16:31 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int	ft_is_same_key(char *key, char *var)
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
		if (ft_is_same_key(key, (*shell_data)->envp[i]))
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
