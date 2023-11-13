/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:37:37 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/13 23:19:46 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int	ft_init(size_t *i, size_t *skip, char ***envp_copy, char **envp)
{
	*i = 0;
	*skip = 0;
	*envp_copy = malloc(sizeof(char *) * (ft_split_len(envp)));
	if (!(*envp_copy))
		return (0);
	return (1);
}

static
int	ft_copy_var(char **envp, char **envp_copy, size_t i, size_t skip)
{
	envp_copy[i - skip] = ft_strdup(envp[i]);
	if (!envp_copy[i - skip])
	{
		ft_free_split(envp_copy);
		return (0);
	}
	return (1);
}

int	ft_envp_unset(t_shell_data **shell_data, char *key)
{
	char	**envp_copy;
	size_t	i;
	size_t	skip;

	envp_copy = NULL;
	if (!ft_init(&i, &skip, &envp_copy, (*shell_data)->envp))
		return (0);
	while ((*shell_data)->envp[i])
	{
		if (!ft_startswith((*shell_data)->envp[i], key))
		{
			if (!ft_copy_var((*shell_data)->envp, envp_copy, i, skip))
				return (0);
		}
		else
			skip = 1;
		i++;
	}
	envp_copy[i - skip] = NULL;
	ft_free_split((*shell_data)->envp);
	(*shell_data)->envp = envp_copy;
	return (1);
}

int	ft_private_envp_unset(t_shell_data **shell_data, char *key)
{
	char	**envp_copy;
	size_t	i;
	size_t	skip;

	envp_copy = NULL;
	if (!ft_init(&i, &skip, &envp_copy, (*shell_data)->envp))
		return (0);
	while ((*shell_data)->envp[i])
	{
		if (!ft_startswith((*shell_data)->envp[i], key))
		{
			if (!ft_copy_var((*shell_data)->envp, envp_copy, i, skip))
				return (0);
		}
		else
			skip = 1;
		i++;
	}
	envp_copy[i - skip] = NULL;
	ft_free_split((*shell_data)->envp);
	(*shell_data)->envp = envp_copy;
	return (1);
}
