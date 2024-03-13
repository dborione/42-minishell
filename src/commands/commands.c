/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:38:32 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 16:28:03 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	return (new_cmd);
}

t_cmd	*ft_get_command(t_args_list *cmd_args, char **paths)
{
	t_cmd	*new_cmd;
	char	**args;
	int		builtin;

	args = ft_extract_args(cmd_args);
	if (!args)
		return (NULL);
	builtin = ft_is_builtin(args[0]);
	new_cmd = ft_new_command(args[0], builtin);
	if (!new_cmd)
	{
		ft_free_split(args);
		return (NULL);
	}
	if (!builtin && !new_cmd->path && !ft_set_path(new_cmd, paths))
	{
		ft_command_not_found(new_cmd->name);
		ft_free_commands(&new_cmd);
		return (NULL);
	}
	else
		new_cmd->args = args;
	return (new_cmd);
}
