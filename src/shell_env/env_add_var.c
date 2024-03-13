/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:29:56 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 16:52:44 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int	ft_free_split_and_return(char **env_copy)
{
	ft_free_split(env_copy);
	return (0);
}

int	ft_envp_add(t_shell_data **shell_data, char *input)
{
	char	**envp_copy;
	size_t	i;

	i = 0;
	envp_copy = malloc(sizeof(char *) * 
			(ft_split_len((*shell_data)->envp) + 2));
	if (!envp_copy)
		return (0);
	while ((*shell_data)->envp[i])
	{
		envp_copy[i] = ft_strdup((*shell_data)->envp[i]);
		if (!envp_copy[i])
			return (ft_free_split_and_return(envp_copy));
		i++;
	}
	envp_copy[i] = ft_var_new_value(input, NULL);
	if (!envp_copy[i])
		return (ft_free_split_and_return(envp_copy));
	envp_copy[i + 1] = NULL;
	ft_free_split((*shell_data)->envp);
	(*shell_data)->envp = envp_copy;
	return (1);
}

int	ft_private_envp_add(t_shell_data **shell_data, char *input)
{
	char	**envp_copy;
	size_t	i;

	i = 0;
	envp_copy = malloc(sizeof(char *) * 
			(ft_split_len((*shell_data)->private_envp) + 2));
	if (!envp_copy)
		return (0);
	while ((*shell_data)->private_envp[i])
	{
		envp_copy[i] = ft_strdup((*shell_data)->private_envp[i]);
		if (!envp_copy[i])
			return (ft_free_split_and_return(envp_copy));
		i++;
	}
	envp_copy[i] = ft_var_new_value(input, NULL);
	if (!envp_copy[i])
		return (ft_free_split_and_return(envp_copy));
	envp_copy[i + 1] = NULL;
	ft_free_split((*shell_data)->private_envp);
	(*shell_data)->private_envp = envp_copy;
	return (1);
}
