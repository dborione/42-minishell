/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_home.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:14:43 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 16:37:12 by dborione         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_envp_get_home(t_shell_data *shell_data)
{
	if (ft_env_has(shell_data->envp, "HOME"))
		return (ft_envp_get_value(shell_data->envp, "HOME"));
	return (shell_data->home);
}
