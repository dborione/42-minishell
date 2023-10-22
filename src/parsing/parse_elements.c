/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:20:45 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/22 14:02:10 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static
int		ft_parse_command(t_shell_data *shell_data, t_lexer_tokens *target)
{
	t_cmd			*cmd;
	int				parent;
	char			**tmp_path;

	tmp_path = ft_split(ft_envp_get_value(shell_data->envp, "PATH"), ':');
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
			waitpid(parent, &(shell_data)->exit_code, 0);
			//if (dup2(STDOUT_FILENO, shell_data->output_fd) == -1)
				//return (EXIT_FAILURE);
			//printf("exit code %d\n", status);
		}
	}
	return (0);
}

static
int		ft_parse_builtin(t_shell_data **shell_data, t_lexer_tokens *target)
{
	if (!ft_strncmp(target->input, "echo", ft_strlen(target->input))
		&& ft_strlen(target->input) == 4)
		return (ft_echo(target));
	if (ft_startswith(target->input, "pwd"))
		return (ft_pwd((*shell_data)->envp));
	if (ft_startswith(target->input, "cd"))
		return (ft_cd(shell_data, target->input));
	if (ft_startswith(target->input, "env"))
		return (ft_env((*shell_data)->envp));
	if (ft_startswith(target->input, "exit"))
		return (ft_exit(shell_data, target->input));
	return (0);
}

void	ft_parse_elements(t_shell_data **shell_data, t_lexer_tokens **lexer_list)
{
	t_lexer_tokens	*target;
	int				exit_code;

	target = *lexer_list;
	while (target)
	{
		if (target->token == CMD)
			exit_code = ft_parse_command(*shell_data, target);
		else if (target->token == BUILTIN)
			exit_code = ft_parse_builtin(shell_data, target);
		target = target->next;
	}
	(*shell_data)->exit_code = exit_code;
}
