/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:29:56 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/04 13:33:57 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_envp_add(char **envp, char **input)
{
	char 	**envp_copy;
	size_t	i;

	i = 0;
	envp_copy = malloc(sizeof(char *) * (ft_split_len(envp) + 2));
	while (envp[i])
	{
		envp_copy[i] = ft_strdup(envp[i]);
		if (!envp_copy[i])
		{
			ft_free_split(envp_copy);
			return (0);
		}
		i++;
	}
	envp_copy[i] = *input;
	envp_copy[i + 1] = NULL;
	ft_free_split(envp);
	envp = envp_copy;
	return (1);
}
