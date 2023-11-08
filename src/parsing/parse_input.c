/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:57:36 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/08 00:21:33 by rbarbiot         ###   ########.fr       */
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

t_cmd *ft_parse_input(t_shell_data **shell_data, char **input)
{
	/*
	---------------------------------
		Insérer les $VAR et $? 
	---------------------------------
	*/
	size_t	start;
	size_t	i;
	t_cmd	*cmds;
	char	**paths;
	// ajouter un type lasso et prendre en charge la suppression de <>
	//char 	*env_var;

	start = 0;
	i = 0;
	cmds = NULL;
	(*shell_data)->pipes = 0;
	paths = ft_split(ft_envp_get_value((*shell_data)->envp, "PATH"), ':'); // créer une commande get_path
    while (paths && input[i])
	{
		if (ft_isequal(input[i], "<"))
		{
			if (ft_isequal(input[i + 1], "<"))
			{
				i++;
				if (!input[i + 1])
				{
					ft_wrong_redirection_syntax(shell_data);
					break ;
				}
				i++;
				ft_heredoc(*shell_data, input[i]);
				if ((*shell_data)->exit_code == CTL_C_EXIT)
				{
					ft_putstr_fd("> \n", STDOUT_FILENO);
					break;
				}
				if (ft_isequal(input[0], "<"))
					break ;
				if (!ft_add_command(&cmds, &input[0], paths, i - 2))
					break ;
				ft_set_cmd_fds(shell_data, cmds);
					break ;
				start = i + 1;
			}
			else
			{
				if (!input[i + 1])
				{
					ft_wrong_redirection_syntax(shell_data);
					break ;
				}
				if (i != start && !ft_add_command(&cmds, &input[start], paths, i - start))
					break ;
				if (!ft_get_infile(shell_data, cmds, input[i + 1]))
				{
					perror("bash");
					//break; break uniquement si aucun pipe
				}
				i++;
				if (!input[i + 1])
					break;
				start = i + 1;	
			}
		}
		else if (ft_isequal(input[i], ">"))
		{
			if (!input[i + 1])
			{
				ft_wrong_redirection_syntax(shell_data);
				break ;
			}
			if (i != start && !ft_add_command(&cmds, &input[start], paths, i - start))
			 	break ;
			//ft_set_cmd_fds(shell_data, cmds);
			if (!ft_get_outfile(shell_data, cmds, input[i + 1]))
			{
				perror("bash");
				//break;
			}
			i += 2;
			if (!input[i])
				break;
			start = i;
		}
		//else if (ft_isequal(input[i], ">>"))
		else if (ft_isequal(input[i], "|"))
		{
			if (!ft_add_command(&cmds, &input[start], paths, i - start))
				break ;
			ft_set_cmd_fds(shell_data, cmds);
			start = i + 1;
			(*shell_data)->pipes++;
			//ft_printf("now = %s\n", input[i + 1]);
		}
		else if (!input[i + 1])
		{
			// ft_printf("now = %s\n", input[start]);
			if (!ft_add_command(&cmds, &input[start], paths, i + 1 - start))
				break ;
			ft_set_cmd_fds(shell_data, cmds);
			break ;
		}
		i++;
	}
	ft_free_split(input);
	if (!paths)
		return (NULL);
	ft_free_split(paths);
	return (cmds);
}
