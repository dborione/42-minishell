/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:38:32 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/22 14:54:46 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_cmd_not_found(char *cmd_name)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putendl_fd(": command not found", 2);
}

static t_cmd	*ft_new_command(char *cmd_name)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->name = ft_strdup(cmd_name);
	if (!new_cmd->name)
	{
		free(new_cmd);
		return (NULL);
	}
	new_cmd->next = NULL;
	new_cmd->path = NULL;
	if (access(new_cmd->name, F_OK) == 0)
	{
		new_cmd->path = ft_strdup(new_cmd->name);
		if (!new_cmd->path)
		{
			free(new_cmd->name);
			free(new_cmd);
			return (NULL);
		}
	}
	return (new_cmd);
}

static int	ft_set_path(t_cmd **new_cmd, char **paths)
{
	int		i;
	char	*tmp_path;

	i = 0;
	while (paths[i])
	{
		tmp_path = ft_strjoin(paths[i], "/");
		if (!tmp_path)
			return (0);
		(*new_cmd)->path = ft_strjoin(tmp_path, (*new_cmd)->name);
		free(tmp_path);
		if (!(*new_cmd)->path)
			return (0);
		if (access((*new_cmd)->path, F_OK) == 0)
			return (1);
		free((*new_cmd)->path);
		(*new_cmd)->path = NULL;
		i++;
	}
	return (0);
}

t_cmd	*ft_get_command(char *cmd, char **paths)
{
	t_cmd	*new_cmd;
	char	**tmp;

	//ft_printf("cmd_name: %s\n", cmd);
	tmp = ft_split_args(cmd);//ft_get_command_args(cmd);
	if (!tmp)
		return (NULL);
	new_cmd = ft_new_command(tmp[0]);
	if (!new_cmd)
	{
		ft_free_split(tmp);
		return (NULL);
	}
	if (!new_cmd->path && !ft_set_path(&new_cmd, paths))
	{
		ft_free_split(tmp);
		if (new_cmd->path)
			free(new_cmd->path);
		ft_cmd_not_found(new_cmd->name); // free car leak en ce moment
		return (NULL); // a retirer quand on fera la loop sur toutes les cmds
	}
	else
		new_cmd->args = tmp;
	return (new_cmd);
}
