/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:20:45 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/18 15:01:20 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static
int		ft_parse_command(t_shell_data *shell_data, t_lexer_tokens *target)
{
	t_cmd			*cmd;
	int				parent;
	int				status;

	// if input == BUILTIN set path to src/builtins
	char **tmp_path = ft_split(ft_envp_get_value(shell_data->envp, "PATH"), ':');
	//ft_printf("cmd_full: %s\n", target->input);
	cmd = ft_get_command(target->input, tmp_path); // je recupere pour le moment uniquement la premiere commande pour tester, en suite j'ai deja prevu la boucle tkt
	ft_free_split(tmp_path);
	//ft_printf("cmd_name: %s, cmd_path: %s\n", cmd->name, cmd->path);
	if (cmd)
	{
		//ft_printf("cmd\n");
		parent = fork();
		if (parent < 0)
			perror("bash");
		if (parent == 0)
			ft_execution(shell_data, cmd);
		else
		{
			waitpid(parent, &status, 0);
			//printf("exit code %d\n", status);
		}
	}
	return (0);
}

static
int		ft_parse_builtin(t_shell_data **shell_data, t_lexer_tokens *target)
{
	if (ft_startswith(target->input, "echo"))
		return (ft_echo(target));
	if (ft_startswith(target->input, "pwd"))
		return (ft_pwd((*shell_data)->envp));
	if (ft_startswith(target->input, "cd"))
		return (ft_cd(shell_data, target->input));
	if (ft_startswith(target->input, "env"))
		return (ft_env((*shell_data)->envp));
		// return (ft_echo(line));
	return (0);
}

void	ft_parse_elements(t_shell_data **shell_data, t_lexer_tokens **lexer_list)
{
	t_lexer_tokens	*target;

	target = *lexer_list;
	while (target)
	{
		if (target->token == CMD)
			ft_parse_command(*shell_data, target);
		else if (target->token == BUILTIN)
			ft_parse_builtin(shell_data, target);
		target = target->next;
	}
	//ft_printf("bye loop\n");
}
