/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:50:42 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 16:53:37 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int	ft_set_shell_path(
	t_shell_data **shell_data, char *relative_shell_path)
{
	char	*absolute_shell_path;
	char	*input;

	absolute_shell_path = ft_get_shell_path((*shell_data)->envp,
			relative_shell_path);
	if (!absolute_shell_path)
		return (0);
	input = ft_strjoin("SHELL=", absolute_shell_path);
	if (!input)
	{
		free(absolute_shell_path);
		return (0);
	}
	if (!ft_envp_set(shell_data, input))
	{
		free(input);
		free(absolute_shell_path);
		return (0);
	}
	free(input);
	free(absolute_shell_path);
	return (1);
}

static
char	*ft_get_new_shell_level(char *shlvl)
{
	int		shlvl_int;

	shlvl_int = 1;
	if (shlvl[0])
	{
		shlvl_int = ft_atoi(shlvl);
		if (shlvl_int < -1)
			shlvl_int = -1;
		else if (shlvl_int >= 999)
		{
			ft_shlvl_to_hight(shlvl_int);
			shlvl_int = 0;
		}
		shlvl_int++;
	}
	return (ft_itoa(shlvl_int));
}

static
int	ft_set_shell_level(t_shell_data **shell_data)
{
	char	*shlvl;
	char	*new_shlvl;

	shlvl = ft_envp_get_value((*shell_data)->envp, "SHLVL");
	new_shlvl = ft_get_new_shell_level(shlvl);
	if (!new_shlvl)
		return (0);
	shlvl = ft_strjoin("SHLVL=", new_shlvl);
	if (!shlvl)
	{
		free(new_shlvl);
		return (0);
	}
	if (!ft_envp_set(shell_data, shlvl))
	{
		free(shlvl);
		free(new_shlvl);
		return (0);
	}
	free(shlvl);
	free(new_shlvl);
	return (1);
}

int	ft_init_envp(t_shell_data **shell_data, char **envp, char *shell_path)
{
	(*shell_data)->envp = ft_envp_copy(envp);
	if (!(*shell_data)->envp)
		return (0);
	if (!ft_set_shell_path(shell_data, shell_path))
		return (0);
	(*shell_data)->private_envp = ft_envp_copy((*shell_data)->envp);
	if (!(*shell_data)->private_envp)
		return (0);
	if (!ft_set_shell_level(shell_data))
		return (0);
	(*shell_data)->home = ft_strdup(
			ft_envp_get_value((*shell_data)->envp, "HOME"));
	if (!(*shell_data)->home)
		return (0);
	return (1);
}
