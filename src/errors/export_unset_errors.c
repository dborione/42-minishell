/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:56:43 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/16 11:57:12 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_export_error(char *arg)
{
	ft_perror("bash: export: `");
	ft_perror(arg);
	ft_perror("': not a valid identifier\n");
	return (1);
}

int	ft_unset_error(char *arg)
{
	ft_perror("bash: unset: `");
	ft_perror(arg);
	ft_perror("': not a valid identifier\n");
	return (1);
}
