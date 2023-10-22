/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_output_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:47:14 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/22 12:48:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_get_outfile(t_shell_data **shell_data, char *tmp)
{
	char	*outfile_path;

	outfile_path = ft_strtrim(tmp, " ");
	if (!outfile_path)
		return (0);
	(*shell_data)->output_fd = open(outfile_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if ((*shell_data)->output_fd == -1)
		return (EXIT_FAILURE);
	return (1);
}
