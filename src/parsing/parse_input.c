/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:57:36 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/29 16:12:46 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int	ft_extract_command(t_lexer_tokens **lexer_list, char *tmp)
{
	char	*res;
	int		success;

	res = ft_strtrim(tmp, " ");
	if (res)
	{
		if (!res[0])
		{
			free(res);
			return (1);
		}
		if (ft_is_builtin(res))
			success = ft_add_token_to_list(lexer_list, &res, BUILTIN);
		else
			success = ft_add_token_to_list(lexer_list, &res, CMD);
		if (success)
			return (1);
		free(res);
		return (0);
	}
	perror("bash");
	return (0);
}

t_lexer_tokens *ft_parse_input(t_shell_data **shell_data, char *line)
{
	char	*tmp;
	size_t	start;
	size_t	i;
    t_lexer_tokens  *lexer_list;

	tmp = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!tmp)
		return (NULL);
	start = 0;
	i = 0;
	(*shell_data)->infile = 0;
	(*shell_data)->outfile = 0;
	lexer_list = NULL;
	tmp[0] = '\0';
    while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			i += 2;
			while (ft_isspace(line[i]))
				i++;
			ft_heredoc(*shell_data, &line[i]);
			if ((*shell_data)->exit_code == CTL_C_EXIT)
			{
				printf("> \n");
				ft_init_shell_sigaction(*shell_data, MAIN);
				free(tmp);
    			return (lexer_list);
			}
			ft_init_shell_sigaction(*shell_data, MAIN);
		}
		if (tmp[0] && i > 0 && line[i] == '<' && !(*shell_data)->infile)
		{
			tmp[i - start] = '\0';
			if (!ft_get_infile(shell_data, tmp))
				perror("bash");
			(*shell_data)->infile = 1;
			i++;
			start = i;
			tmp[0] = '\0';
		}
		else if (line[i] == '>')
		{
			tmp[i - start] = '\0';
			if (!ft_extract_command(&lexer_list, tmp))
			{
				(*shell_data)->exit = 1;
				//ajouter le clear des lexe
			}
			i++;
			while (ft_isspace(line[i]))
				i++;
			if (!ft_get_outfile(shell_data, &line[i]))
				perror("bash");
			(*shell_data)->outfile = 1;
			break;
			start = i;
			tmp[0] = '\0';
		}
		else if (line[i] == '|')
		{
			tmp[i - start] = '\0';
			if (!ft_extract_command(&lexer_list, tmp))
			{
				(*shell_data)->exit = 1;
				//ajouter le clear des lexe
			}
			start = ++i;
			tmp[0] = '\0';
		}
		else if (line[i] == '$')
		{
			i++;
			if (line[i] == '?')
			{
				ft_putstr_fd("bash: ", 2);
				ft_putnbr_fd((*shell_data)->exit_code, 2);
				ft_putendl_fd(": command not found", 2);
			}
		}
		tmp[i - start] = line[i];
		i++;
	}
	tmp[i - start] = '\0';
    if (tmp[0] && !ft_extract_command(&lexer_list, tmp))
	{
		(*shell_data)->exit = 1;
		//ajouter le clear des lexe
	}
	free(tmp);
    return (lexer_list);
}
