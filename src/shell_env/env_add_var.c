/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:29:56 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/24 15:54:04 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_envp_add(t_shell_data **shell_data, char **input) // le seg fault vient d'ici 
{
	char 	**envp_copy;
	size_t	i;

	i = 0;
	envp_copy = malloc(sizeof(char *) * (ft_split_len((*shell_data)->envp) + 2));
	while ((*shell_data)->envp[i])
	{
		envp_copy[i] = ft_strdup((*shell_data)->envp[i]);
		if (!envp_copy[i])
		{
			ft_free_split(envp_copy);
			return (0);
		}
		i++;
	}
	envp_copy[i] = *input;
	envp_copy[i + 1] = NULL;
	ft_free_split((*shell_data)->envp);
	(*shell_data)->envp = envp_copy;
	return (1);
}
