/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:37:37 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/24 15:54:04 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int	ft_init(size_t *i, size_t *skip, char **envp_copy, char **envp)
{
	*i = 0;
	*skip = 0;
	envp_copy = malloc(sizeof(char *) * (ft_split_len(envp)));
	if (!envp_copy)
		return (0);
	return (1);
}

int ft_envp_unset(char **envp, char *key)
{
	char 	**envp_copy;
	size_t	i;
	size_t	skip;

	envp_copy = NULL;
	if (!ft_init(&i, &skip, envp_copy, envp))
		return (0);
	while (envp[i])
	{
		if (!ft_startswith(envp[i], key))
		{
			envp_copy[i - skip] = ft_strdup(envp[i]);
			if (!envp_copy[i - skip])
			{
				ft_free_split(envp_copy);
				return (0);
			}
		}
		else
			skip = 1;
		i++;
	}
	envp_copy[i - skip] = NULL;
	ft_free_split(envp);
	envp = envp_copy;
	return (1);
}
