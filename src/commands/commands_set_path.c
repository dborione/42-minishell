/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_set_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:09:39 by dborione          #+#    #+#             */
/*   Updated: 2023/11/17 17:31:53 by dborione         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int	ft_set_absolute_path(t_cmd *new_cmd)
{
	if (new_cmd->name[0] && access(new_cmd->name, F_OK) == 0)
	{
		new_cmd->path = ft_strdup(new_cmd->name);
		if (!new_cmd->path)
		{
			free(new_cmd->name);
			free(new_cmd);
			return (0);
		}
		return (1);
	}
	return (0);
}

static
int	ft_set_relative_path(t_cmd *new_cmd)
{
	if (new_cmd->name[0] && !new_cmd->builtin
		&& ft_startswith(new_cmd->name, "./")
		&& access(new_cmd->name, F_OK) == 0
	)
	{
		new_cmd->path = ft_strdup(new_cmd->name);
		if (!new_cmd->path)
		{
			free(new_cmd->name);
			free(new_cmd);
			return (0);
		}
	}
	return (1);
}

static
int	ft_free_split_and_return(char **cmd_paths, int ret)
{
	ft_free_split(cmd_paths);
	return (ret);
}

static
int	ft_join_paths(t_cmd *new_cmd, char **paths, char **cmd_paths, int j)
{
	int		i;
	char	*tmp_path;

	i = 0;
	while (paths[i])
	{
		tmp_path = ft_strjoin(paths[i], "/");
		if (!tmp_path)
			return (ft_free_split_and_return(cmd_paths, 0));
		new_cmd->path = ft_strjoin(tmp_path, cmd_paths[j]);
		free(tmp_path);
		if (!new_cmd->path)
			return (ft_free_split_and_return(cmd_paths, 0));
		if (access(new_cmd->path, F_OK) == 0)
			return (ft_free_split_and_return(cmd_paths, 1));
		free(new_cmd->path);
		new_cmd->path = NULL;
		i++;
	}
	return (-1);
}

int	ft_set_path(t_cmd *new_cmd, char **paths)
{
	int		ret;
	int		j;
	char	**cmd_paths;

	if (!new_cmd->name[0])
		return (0);
	if (ft_set_absolute_path(new_cmd))
		return (1);
	j = 0;
	ret = 0;
	cmd_paths = ft_split(new_cmd->name, '/');
	if (!cmd_paths)
		return (0);
	while (cmd_paths[j])
		j++;
	j -= 1;
	ret = ft_join_paths(new_cmd, paths, cmd_paths, j);
	if (ret != -1)
		return (ret);
	ft_free_split(cmd_paths);
	free(new_cmd->path);
	new_cmd->path = NULL;
	return (ft_set_relative_path(new_cmd));
}
