/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:57:36 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/03 11:01:30 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	paths = ft_split(ft_envp_get_value((*shell_data)->envp, "PATH"), ':'); // créer une commande get_path
    while (paths && input[i])
	{
		if (ft_isequal(input[i], "<"))
		{
			if (!input[i + 1])
			{
				ft_wrong_redirection_syntax(shell_data);
				break ;
			}
			if (i != start && !ft_add_command(&cmds, &input[start], paths, i - start))
				break ;
			if (!ft_get_infile(shell_data, input[i + 1]))
			{
				perror("bash");
				//break; break uniquement si aucun pipe
			}
			i+=2;
			if (!input[i])
				break;
			start = i;
		}
		//else if (ft_isequal(input[i], "<<"))
		else if (ft_isequal(input[i], ">"))
		{
			if (!input[i + 1])
			{
				ft_wrong_redirection_syntax(shell_data);
				break ;
			}
			if (i != start && !ft_add_command(&cmds, &input[start], paths, i - start))
				break ;
			if (!ft_get_outfile(shell_data, input[i + 1]))
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
			start = i + 1;
			//ft_printf("now = %s\n", input[i + 1]);
		}
		else if (!input[i + 1])
		{
			//ft_printf("now = %s\n", input[i]);
			if (!ft_add_command(&cmds, &input[start], paths, i + 1 - start))
				break ;
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
