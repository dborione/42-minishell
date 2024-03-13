/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:22:06 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 18:42:59 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
void	ft_print_export_env(char **envp)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		key = ft_envp_get_key(envp[i]);
		if (!key)
			break ;
		printf("declare -x %s", key);
		value = ft_envp_get_value(envp, key);
		free(key);
		if (value[0])
		{
			printf("=");
			printf("\"%s\"", value);
		}
		printf("\n");
		i++;
	}
}

int	ft_export_env(t_shell_data **shell_data)
{
	ft_free_split((*shell_data)->envp);
	(*shell_data)->envp = ft_envp_copy((*shell_data)->private_envp);
	if (!(*shell_data)->envp)
		return (0);
	ft_print_export_env((*shell_data)->envp);
	return (1);
}
