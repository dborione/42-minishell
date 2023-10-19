/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:32:57 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/19 17:09:07 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static
size_t	ft_split_from_quotes(t_cmd_split **cmd_split, char *str_before, char *str_after)
{
	char	*tmp;
	size_t	len;

	if (str_before[0] && !ft_add_command_arg(cmd_split, str_before))
		return (0);
	tmp = ft_get_with_quotes(str_after);
	//ft_putendl_fd(tmp, 1);
	if (!tmp)
		return (0);
	if (!ft_add_command_arg(cmd_split, tmp))
	{
		free(tmp);
		return (0);
	}
	len = ft_strlen(tmp);
	free(tmp);
	return (len + 2);
}

static
t_cmd_split	*ft_commands_args_with_quotes(char *full_cmd, size_t len)
{
	char		*tmp;
	size_t		i;
	size_t		start;
	t_cmd_split	*cmd_split;

	cmd_split = NULL;
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (ft_isspace(full_cmd[i]))
			i++;
	start = i;
	while (full_cmd[i])
	{
		if (ft_isspace(full_cmd[i]))
		{
			tmp[i - start] = '\0';
			if (!ft_add_command_arg(&cmd_split, tmp))
			{
				ft_free_command_args(&cmd_split);
				free(tmp);
				return (NULL);
			}
			while (ft_isspace(full_cmd[i]))
				i++;
			start = i;
		}
		if ((full_cmd[i] == '\'' || full_cmd[i] == '"') && ft_has_endof_quotes(&full_cmd[i], full_cmd[i]))
		{
			tmp[i - start] = '\0';
			start = ft_split_from_quotes(&cmd_split, tmp, &full_cmd[i]);
			if (!start)
			{
				ft_free_command_args(&cmd_split);
				free(tmp);
				return (NULL);
			}
			i += start;
			while (ft_isspace(full_cmd[i]))
				i++;
			start = i;
		}
		tmp[i - start] = full_cmd[i];
		i++;
	}
	tmp[i - start] = '\0';
	if (tmp[0])
	{
		if (!ft_add_command_arg(&cmd_split, tmp))
		{
			ft_free_command_args(&cmd_split);
			free(tmp);
			return (NULL);
		}
	}
	free(tmp);
	return (cmd_split);
}

static
char	**ft_cmd_split_to_str_split(t_cmd_split **cmd_split)
{
	t_cmd_split	*target;
	size_t		i;
	char		**res;

	target = *cmd_split;
	i = 0;
	while (target)
	{
		target = target->next;
		i++;
	}
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	target = *cmd_split;
	while (target)
	{
		res[i] = target->arg;
		target = target->next;
		i++;
	}
	res[i] = NULL;
	i = 0;
	return (res);
}

char	**ft_get_command_args(char *full_cmd)
{
	char		**res;
	size_t		len;
	t_cmd_split	*cmd_split;

	len = ft_strlen(full_cmd);
	if (!ft_memchr(full_cmd, '"', len) && !ft_memchr(full_cmd, '\'', len))
		return (ft_split(full_cmd, ' '));
	cmd_split = ft_commands_args_with_quotes(full_cmd, len);
	res = ft_cmd_split_to_str_split(&cmd_split);
	if (!res)
	{
		ft_free_command_args(&cmd_split);
		return (NULL);
	}
	ft_free_command_args(&cmd_split);
	return (res);
}
