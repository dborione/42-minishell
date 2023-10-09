/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:17:18 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/04 14:23:25 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
