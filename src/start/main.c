/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 00:42:05 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/14 10:27:29 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
void	ft_destroy_shell(t_shell_data **shell_data)
{
	if (shell_data && *shell_data)
	{
		ft_free_split((*shell_data)->envp);
		ft_free_split((*shell_data)->private_envp);
		free(*shell_data);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell_data	*shell_data;
	int				error_code;

	error_code = 0;
	if (argc == 1 && ft_isequal(argv[0], "./minishell"))
	{
		if (!ft_init_all(&shell_data, argv[0], envp))
		{
			ft_destroy_shell(&shell_data);
			perror("bash");
			return (EXIT_FAILURE);
		}
		ft_get_input(&shell_data);
		ft_free_split(shell_data->envp);
		ft_free_split(shell_data->private_envp);
		if (shell_data)
			error_code = shell_data->exit_code;
		else
			error_code = 127;
		ft_destroy_shell(&shell_data);
	}
	else
		ft_putendl_fd("Error: just ./minishell", 2);
	exit (error_code);
}
