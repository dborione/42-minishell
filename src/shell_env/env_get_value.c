/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:17:18 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/16 23:21:06 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_var_get_value(char *var)
{
	size_t	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (&var[i + 1]);
}

char	*ft_envp_get_var(char **envp, char *var)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(ft_envp_get_key(var), "=");
	if (!tmp)
		return (NULL);
	while (envp[i])
	{
		if (ft_startswith(envp[i], tmp))
		{
			free(tmp);
			return (envp[i]);
		}
		i++;
	}
	free(tmp);
	return ("");
}

char	*ft_envp_get_value(char **envp, char *key)
{
	size_t	i;
	size_t	start;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	while (envp[i])
	{
		if (ft_startswith(envp[i], tmp))
		{
			start = ft_strlen(tmp);
			free(tmp);
			return (&envp[i][start]);
		}
		i++;
	}
	free(tmp);
	return ("");
}
