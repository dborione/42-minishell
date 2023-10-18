/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:30:36 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/18 15:15:08 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			//ft_printf(">>>> '%s' <<<<\n", *input);
			(*shell_data)->envp[i] = *input;
			return (1);
		}
		// else
		// {
		// 	ft_printf(">key %s >value %s\n", key, envp[i]);
		// }
		i++;
	}
	free(key);
	//ft_env(envp);
	//ft_printf("add %d\n", i);
	ft_envp_add(shell_data, input);
	//ft_env(envp);
	return (1);
}
