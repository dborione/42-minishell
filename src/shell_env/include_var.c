/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:32:27 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/10 22:06:12 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
char	*ft_new_include(char *str, size_t len)
{
	char	*res;
	size_t	i;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static
char	*ft_var_join(char *s1, char *s2, size_t len)
{
	int		i;
	int		y;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_new_include(s2, len));
	i = -1;
	y = -1;
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	while (s1[++y])
		res[y] = s1[y];
	while (++i < (int)len && s2 && s2[i])
		res[y + i] = s2[i];
	res[y + i] = '\0';
	free(s1);
	return (res);
}

static
char	*ft_get_value(t_data_split *data, char *str, size_t end)
{
	char	*tmp;
	char	*res;

	if (str[0] == '?')
		return (ft_itoa(data->exit_code));
	tmp = ft_strdup(str);
	if (!tmp)
		return (NULL);
	tmp[end] = '\0';
	res = ft_envp_get_value(data->envp, tmp);
	free(tmp);
	return (res);
}

int		ft_is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*ft_include_var(t_data_split *data, char *input)
{
	size_t		i;
	size_t		start;
	char		*tmp;
	char		*res;

	i = 0;
	start = 0;
	res = NULL;
	while (input[i])
	{
		if (input[i] == '$' && (ft_is_var_char(input[i + 1]) ||input[i + 1] == '?'))
		{
			res = ft_var_join(res, &input[start], i++);
			if (!res)
				return (0);
			start = i;
			while (input[i] && input[i]!= '?' &&  !ft_isspace(input[i]))
				i++;
			tmp = ft_get_value(data, &input[start], i);
			if (!tmp)
			{
				free(res);
				return (NULL);
			}
			res = ft_var_join(res, tmp, ft_strlen(tmp));
			if (!res)
				return (0);
			start = ++i;
		}
		else
			i++;
	}
	if (res)
		return (res);
	return (input);
}
