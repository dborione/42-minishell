/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:57:36 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/22 02:00:04 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static
void	ft_print_lst(t_lexer_tokens **head_lexer_lst)
{
    t_lexer_tokens *current;

    current = *head_lexer_lst;
    while (current)
    {
        printf("%s - %d\n", current->input, current->token);
        current = current->next;
    }
}

// static
// char	*ft_cut_between_quotes(char *str, size_t len)
// {
// 	char	*res;
// 	size_t	i;

// 	res = malloc(sizeof(char) * (len + 1));
// 	i = 0;
// 	while (str[i])
// 	{
// 		/* code */
// 	}
	
// }

// static
// char	*ft_get_between_quotes(char *str)
// {
// 	char	quote;
// 	int		close_quote;
// 	size_t	i;

// 	quote = str[0];
// 	close_quote = 0;
// 	i = 1;
// 	while (str[i])
// 	{
// 		if (!str[i] == quote)
// 		{
// 			close_quote = 1;
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (close_quote)
// 		return (i);
// 	return (0);
// }

static
int	ft_add_token_to_list(t_lexer_tokens **lexer_list, char **input, int token)
{
    t_lexer_tokens *newnode;
    t_lexer_tokens *tmp_lexer_list;

    tmp_lexer_list = *lexer_list;
    newnode = malloc(sizeof(t_lexer_tokens));
    if (!newnode)
        return (0);
   	newnode->input = *input;
    newnode->token = token;
    newnode->next = NULL;
    if (!*lexer_list)
    {
        *lexer_list = newnode;
        return (1);
    }
    while (tmp_lexer_list)
    {
        if (!tmp_lexer_list->next)
            break;
        tmp_lexer_list = tmp_lexer_list->next;
    }
    tmp_lexer_list->next = newnode;
    return (1);
}

static
int	ft_get_infile(t_shell_data **shell_data, char *tmp)
{
	char	*infile_path;

	infile_path = ft_strtrim(tmp, " ");
	if (!infile_path)
		return (0);
	//ft_printf("infile: %s\n", infile_path);
	if (access(infile_path, F_OK) == 0 && access(infile_path, R_OK) == 0)
	{
		(*shell_data)->input_fd = open(infile_path, O_RDONLY, 0644);
		if ((*shell_data)->input_fd == -1)
			return (0);
		return (1);
	}
	return (0);
}

static
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

static
int	ft_extract_command(t_lexer_tokens **lexer_list, char *tmp)
{
	char	*res;

	res = ft_strtrim(tmp, " ");
	if (res)
	{
		//ft_printf("cmd_trim: %s\n", res);
		if (ft_is_builtin(res))
			ft_add_token_to_list(lexer_list, &res, BUILTIN); // erreurs de add à gerer
		else
			ft_add_token_to_list(lexer_list, &res, CMD);
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
	int		infile;
    t_lexer_tokens  *lexer_list;

	tmp = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!tmp)
		return (NULL);
	start = 0;
	i = 0;
	infile = 0;
	lexer_list = NULL;
	tmp[0] = '\0';
    while (line[i])
	{
		if (tmp[0] && i > 0 && ft_isspace(line[i - 1]) && line[i] == '<' && !infile)
		{
			tmp[i - start] = '\0';
			if (!ft_get_infile(shell_data, tmp))
				perror("bash");
			infile = 1;
			start = i;
		}
		else if (tmp[0] && i > 0 && ft_isspace(line[i - 1]) && line[i] == '>' && !infile)
		{
			tmp[i - start] = '\0';
			if (!ft_extract_command(&lexer_list, tmp))
			{
				// prendre en charge les cas d'erreurs ici
			}
			i++;
			while (ft_isspace(line[i]))
				i++;
			if (!ft_get_outfile(shell_data, &line[i]))
				perror("bash");
			break;
			start = i;
			tmp[0] = '\0';
		}
		else if (line[i] == '|')
		{
			tmp[i - start] = '\0';
			if (!ft_extract_command(&lexer_list, tmp))
			{
				// prendre en charge les cas d'erreurs ici
			}
			infile = 1;
			start = ++i;
			tmp[0] = '\0';
		}
		tmp[i - start] = line[i];
		i++;
	}
	tmp[i - start] = '\0';
    if (tmp[0] && !ft_extract_command(&lexer_list, tmp))
	{
		// prendre en charge les cas d'erreurs ici
	}
	free(tmp);
    //ft_print_lst(&lexer_list);
    return (lexer_list);
}
