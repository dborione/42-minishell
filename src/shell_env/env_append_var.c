/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_append_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:14:17 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 16:36:36 by dborione         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
char	*ft_var_without_plus(char *var)
{
	char	*res;
	size_t	i;
	size_t	y;

	res = malloc(sizeof(char) * ft_strlen(var));
	if (!res)
		return (NULL);
	i = 0;
	y = 0;
	while (var[i])
	{
		if (var[i] != '+')
		{
			res[y] = var[i];
			y++;
		}
		i++;
	}
	res[y] = '\0';
	return (res);
}

static
int	ft_var_append_mode(char *var)
{
	size_t	i;

	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (var[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_var_new_value(char *var, char *old_var)
{
	if (ft_var_append_mode(var))
	{
		if (old_var)
			return (ft_strjoin(old_var, ft_var_get_value(var)));
		return (ft_var_without_plus(var));
	}
	else
		return (ft_strdup(var));
}
