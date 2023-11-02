/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:38:32 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/02 22:30:11 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
void	ft_cmd_not_found(char *cmd_name)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putendl_fd(": command not found", 2);
}

static
t_cmd	*ft_new_command(char *cmd_name, int builtin)
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
	new_cmd->builtin = builtin;
	new_cmd->next = NULL;
	new_cmd->path = NULL;
	if (!builtin && access(new_cmd->name, F_OK) == 0)
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

static
int	ft_set_path(t_cmd **new_cmd, char **paths)
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

t_cmd	*ft_get_command(char **cmd_args, char **paths, size_t end)
{
	t_cmd	*new_cmd;
	char	**new_cmd_args;
	int		builtin;

	ft_printf("lets: %s\n", cmd_args[0]);
	new_cmd_args = ft_extract_args(cmd_args, end);
	if (!new_cmd_args)
		return (NULL);
	builtin = ft_is_builtin(new_cmd_args[0]);
	//tmp = ft_split_args(cmd);
	new_cmd = ft_new_command(new_cmd_args[0], builtin);
	if (!new_cmd)
	{
		//ft_free_split(tmp);
		return (NULL);
	}
	if (!builtin && !new_cmd->path && !ft_set_path(&new_cmd, paths))
	{
		//ft_free_split(tmp);
		if (new_cmd->path)
			free(new_cmd->path);
		ft_cmd_not_found(new_cmd->name); // free car leak en ce moment
		return (NULL);
	}
	else
		new_cmd->args = new_cmd_args;
	ft_printf("no error: %s\n", new_cmd->name);
	return (new_cmd);
}

// void		ft_add_command(t_cmd **cmds, t_cmd *new_cmd)
// {
// 	t_cmd	*target;

// 	if (!cmds)
// 		return ;
// 	if (!*cmds)
// 	{
// 		new_cmd->id = 0;
// 		*cmds = new_cmd;
// 	}
// 	else
// 	{
// 		target = (*cmds);
// 		while (target->next)
// 			target = target->next;
// 		new_cmd->id = target->id + 1;
// 		target->next = new_cmd;
// 	}
// }

int		ft_add_command(t_cmd **cmds, char **cmd_args, char **paths, size_t end)
{
	t_cmd	*target;

	if (!cmds)
		return (0);
	if (!*cmds)
	{
		*cmds = ft_get_command(cmd_args, paths, end);
		// erreurs de création de commande à prendre en compte
		ft_printf("first cmd = %s\n", cmd_args[0]);
		if (!*cmds)
			return (0);
	}
	else
	{
		ft_printf("next cmd = %s\n", cmd_args[0]);
		target = (*cmds);
		while (target->next)
			target = target->next;
		target->next = ft_get_command(cmd_args, paths, end);
		if (!target->next)
			return (0);
		// exit 127 : erreurs de création de commande à prendre en compte
		return (1);
	}
	return (1);
}