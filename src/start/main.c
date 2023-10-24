/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 00:42:05 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/23 12:17:51 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_shell_data	*shell_data;

	if (argc == 1)
	{
		if (!ft_init_shell(&shell_data, argv[0], envp))
		{
			perror("bash");
			//system("leaks minishell");
			return (EXIT_FAILURE);
		}
		//ft_init_shell_sigaction(shell_data);
		ft_get_input(&shell_data);
		ft_free_split(shell_data->envp);
		free(shell_data);
	}
	else
		ft_putendl_fd("Error: just ./minishell", 2);
	return (0);
}
