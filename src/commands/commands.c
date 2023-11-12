/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:38:32 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/12 22:18:56 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static
// void	ft_cmd_not_found(char *cmd_name)
// {
// 	ft_putstr_fd("bash: ", 2);
// 	ft_putstr_fd(cmd_name, 2);
// 	ft_putendl_fd(": command not found", 2);
// }

static
void	ft_init_command(t_cmd *new_cmd, int builtin)
{
	new_cmd->id = 0;
	new_cmd->pid = -1;
	new_cmd->builtin = builtin;
	new_cmd->next = NULL;
	new_cmd->path = NULL;
	new_cmd->input_fd = STDIN_FILENO;
	new_cmd->output_fd = STDOUT_FILENO;
	new_cmd->exit_code = 42;
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
	ft_init_command(new_cmd, builtin);
	if (new_cmd->name[0] && !builtin && access(new_cmd->name, F_OK) == 0)
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
int		ft_set_path(t_cmd **new_cmd, char **paths)
{
	int		i;
	char	*tmp_path;

	if (!(*new_cmd)->name[0])
		return (0);
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
	free((*new_cmd)->path);
	(*new_cmd)->path = NULL;
	return (1);
}

void	ft_set_command_fds(t_shell_data **shell_data, t_cmd *cmds)
{
	t_cmd	*target;

	if (!cmds)
		return ;
	target = cmds;
	while (target->next)
		target = target->next;
	target->input_fd = (*shell_data)->input_fd;
	(*shell_data)->input_fd = STDIN_FILENO;
	target->output_fd = (*shell_data)->output_fd;
	(*shell_data)->output_fd = STDOUT_FILENO;
}

t_cmd	*ft_get_command(t_args_list *cmd_args, char **paths)
{
	t_cmd	*new_cmd;
	char	**new_cmd_args;
	int		builtin;

	new_cmd_args = ft_extract_args(cmd_args);
	if (!new_cmd_args)
		return (NULL);
	builtin = ft_is_builtin(new_cmd_args[0]);
	new_cmd = ft_new_command(new_cmd_args[0], builtin);
	if (!new_cmd)
		return (NULL);
	if (!builtin && !new_cmd->path && !ft_set_path(&new_cmd, paths))
	{
		if (new_cmd->path)
			free(new_cmd->path);
		ft_command_not_found(new_cmd->name); // free car leak en ce moment
		return (NULL);
	}
	else
		new_cmd->args = new_cmd_args;
	return (new_cmd);
}
