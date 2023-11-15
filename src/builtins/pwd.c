/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:29:01 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/15 22:24:05 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

int ft_pwd(t_shell_data *shell_data)
{
	char	cwd[PATH_MAX];

	if (shell_data->pwd)
	{
		ft_putendl_fd(shell_data->pwd, 1);
		return (0);
	}
	if (!getcwd(cwd, PATH_MAX))
	{
		perror("bash: pwd");
		return (EXIT_FAILURE);
	}
    ft_putendl_fd(cwd, 1);
    return (0);
}