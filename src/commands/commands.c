/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:38:32 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/06 16:14:13 by rbarbiot         ###   ########.fr       */
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
	tmp = ft_get_command_args(cmd);
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

// static void	ft_add_command(t_cmd **cmds, t_cmd *new_cmd)
// {
// 	t_cmd	*target;

// 	if (!cmds)
// 		return ;
// 	if (!*cmds)
// 		*cmds = new_cmd;
// 	else
// 	{
// 		target = (*cmds);
// 		while (target->next)
// 			target = target->next;
// 		target->next = new_cmd;
// 	}
// }

// int	ft_get_commands(t_pipex **data, char **argv)
// {
// 	int		i;
// 	t_cmd	*new_cmd;

// 	(*data)->cmds = NULL;
// 	(*data)->cmds = ft_get_command(argv[2], (*data)->paths);
// 	if (!(*data)->cmds)
// 		return (-1);
// 	i = 3;
// 	new_cmd = (*data)->cmds->next;
// 	while (argv[i] && argv[i + 1])
// 	{
// 		new_cmd = ft_get_command(argv[i], (*data)->paths);
// 		if (!new_cmd)
// 			return (-1);
// 		if (!new_cmd->path)
// 		{
// 			free(new_cmd->name);
// 			free(new_cmd);
// 			return (127);
// 		}
// 		i++;
// 		ft_add_command(&(*data)->cmds, new_cmd);
// 	}
// 	return (1);
// }
