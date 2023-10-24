/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:30:36 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/24 15:54:04 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		ft_envp_set(t_shell_data **shell_data, char **input)
{
	size_t	i;
	char	*key;

	//ft_env(*envp);
	key = ft_envp_get_key(*input);
	if (!key)
		return (0);
	i = 0;
	while ((*shell_data)->envp[i])
	{
		if (ft_startswith((*shell_data)->envp[i], key))
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
