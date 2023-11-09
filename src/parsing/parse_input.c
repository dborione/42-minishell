/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:57:36 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/09 12:20:17 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
void	ft_set_cmd_fds(t_shell_data **shell_data, t_cmd *cmds)
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


t_cmd *ft_parse_input(t_shell_data **shell_data, t_args_list *args)
{
	t_args_list	*target;
	size_t	skip;
	t_cmd	*cmds;
	char	**paths;

	cmds = NULL;
	(*shell_data)->pipes = 0;
	paths = ft_split(ft_envp_get_value((*shell_data)->envp, "PATH"), ':'); // créer une commande get_path
    target = args;
	skip = 0;
	while (paths && target)
	{
		if (target->separator && ft_isequal(target->value, "<"))
		{
			if (!target->next)
			{
				ft_wrong_redirection_syntax(shell_data);
				break ;
			}
			if (!ft_get_infile(shell_data, cmds, target->next->value))
			{
				perror("bash");
			}
			target = target->next->next;
			if (!target)
				break;
		}
		else if (target->separator && ft_isequal(target->value, "<<"))
		 {
			if (!target->next)
			{
				ft_wrong_redirection_syntax(shell_data);
				break ;
			}
			//ft_heredoc(*shell_data, target); à remettre
			if ((*shell_data)->exit_code == CTL_C_EXIT)
			{
				ft_putstr_fd("> \n", STDOUT_FILENO);
				break;
			}
		}
		else if (target->separator && ft_isequal(target->value, ">"))
		{
			ft_printf("inside job\n");
			if (!target->next)
			{
				ft_get_outfile(shell_data, cmds, NULL);
				break ;
			}
			// if (i != start && !ft_add_command(&cmds, target->value, paths, i - start))
			//  	break ;
			//ft_set_cmd_fds(shell_data, cmds);
			if (!ft_get_outfile(shell_data, cmds, target->next->value))
			{
				perror("bash");
				//break;
			}
			target = target->next->next;
			if (!target)
				break;
		}
		//else if (ft_isequal(target->value, ">>"))
		else if (target->separator && ft_isequal(target->value, "|"))
		{
			//ft_set_cmd_fds(shell_data, cmds);
			(*shell_data)->pipes++;
			target = target->next;
			skip = 0;
			//ft_printf("now = %s\n", target->next);
		}
		else if (!skip)
		{
			skip = ft_add_command(&cmds, target, paths);
			if (!skip)
				break ;
			ft_set_cmd_fds(shell_data, cmds);
		}
		else
			target = target->next;
	}
	if (!paths)
		return (NULL);
	ft_free_split(paths);
	return (cmds);
}
