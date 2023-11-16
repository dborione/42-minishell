/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:57:27 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/16 11:57:36 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cd_errors(char *cmd_name, char *msg)
{
	ft_perror("bash: cd: ");
	ft_perror(cmd_name);
	ft_perror(msg);
	return (1);
}
