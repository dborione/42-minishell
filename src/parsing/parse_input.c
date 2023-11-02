/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:57:36 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/02 22:45:26 by rbarbiot         ###   ########.fr       */
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
			if (!ft_get_infile(shell_data, input[i + 1]))
			{
				perror("bash");
				break;
			}
			(*shell_data)->infile = 1;
			i+=2;
			start = i;
		}
		//else if (ft_isequal(input[i], "<<"))
		else if (ft_isequal(input[i], ">"))
		{
			if (!ft_get_outfile(shell_data, input[i]))
			{
				perror("bash");
				break;
			}
			(*shell_data)->outfile = 1;
			start = ++i;
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
		// else if (line[i] == '$')
		// {
		// 	i++;
		// 	if (line[i] == '?')
		// 	{
		// 		ft_putstr_fd("bash: ", 2);
		// 		ft_putnbr_fd((*shell_data)->exit_code, 2);
		// 		ft_putendl_fd(": command not found", 2);
		// 	}
		// 	env_var = ft_envp_get_value((*shell_data)->envp, &line[i]);
		// 	*line = *env_var;
		// }
	}
	ft_free_split(input);
	if (!paths)
		return (NULL);
	ft_free_split(paths);
	return (cmds);
}
