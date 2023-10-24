/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:20:45 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/24 01:31:38 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static
void	ft_parse_execution(t_shell_data **shell_data, t_cmd **cmds)
{
	pid_t	parent;

	if (!(*cmds)->next && (*cmds)->builtin)
		(*shell_data)->exit_code = ft_execute_builtin(shell_data, *cmds);
	else
	{
		parent = fork();
		if (parent < 0)
			perror("bash");
		if (parent == 0)
			ft_execution(shell_data, *cmds);
		else
			waitpid(parent, &(*shell_data)->exit_code, 0);
		// free cmds
	}
}

static
t_cmd	*ft_parse_command(t_shell_data *shell_data, t_lexer_tokens *target)
{
	t_cmd			*cmd;
	char			**tmp_path;

	tmp_path = ft_split(ft_envp_get_value(shell_data->envp, "PATH"), ':');
	cmd = ft_get_command(target->input, tmp_path, target->token == BUILTIN);
	ft_free_split(tmp_path);
	//cmd->id = 0; //segfault here -> je l'ai mis dans ft_new_command
	if (!cmd)
		return (NULL);
	return (cmd);
}

void	ft_parse_elements(t_shell_data **shell_data, t_lexer_tokens **lexer_list)
{
	t_lexer_tokens	*target;
	t_cmd			*cmds;
	t_cmd			*new_cmd;

	target = *lexer_list;
	cmds = ft_parse_command(*shell_data, target);
	if (!cmds)
	{
		ft_printf("cmd failed\n");
		return ;
	}
	ft_printf("target: %s\n", target->input);
	new_cmd = cmds->next;
	while (target->next)
	{
		target = target->next;
		ft_printf("target: %s\n", target->input);
		new_cmd = ft_parse_command(*shell_data, target);
		if (!new_cmd)
			return ;
		if (!new_cmd->builtin && !new_cmd->path)
		{
			free(new_cmd->name);
			free(new_cmd);
			perror("bash");
			return ;
		}
		ft_add_command(&cmds, new_cmd);
		// t_cmd	*target2;

		// target2 = cmds;
		// while (target2)
		// {
		// 	ft_printf("%d\n", target2->id);
		// 	target2 = target2->next;
		// }
	}
	ft_parse_execution(shell_data, &cmds);
}
