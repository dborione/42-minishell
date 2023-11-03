/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_output_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:47:14 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/03 11:24:41 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_get_outfile(t_shell_data **shell_data, char *outfile_path)
{
	
	if ((*shell_data)->outfile)
		close((*shell_data)->output_fd);
	(*shell_data)->output_fd = open(outfile_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if ((*shell_data)->output_fd == -1)
	{
		//ft_printf("fail outfile: %s\n", outfile_path);
		(*shell_data)->outfile = 0;
		(*shell_data)->exit_code = EXIT_FAILURE;
		return (0);
	}
	(*shell_data)->outfile = 1;
	//ft_printf("outfile: %s\n", outfile_path);
	return (1);
}
