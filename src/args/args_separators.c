/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_separators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:16:55 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/15 00:19:12 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_speparators(char *input, size_t i)
{
	return (input[i + 1]
		&& ((input[i] == '<' && input[i + 1] == '<')
		||  (input[i] == '>' && input[i + 1] == '>')));
}

int	ft_is_invalid_args_separator(t_shell_data **shell_data, char *input)
{
	if (ft_startswith(input, "||"))
		ft_wrong_tokens_syntax(shell_data, "||");
	else if (ft_startswith(input, "<<<"))
		ft_wrong_tokens_syntax(shell_data, "<");
	else if (ft_startswith(input, ">>>"))
		ft_wrong_tokens_syntax(shell_data, ">");
	else
		return (0);
	return (1);
}

static
void	ft_set_type_separator(t_args_list **args_list)
{
	t_args_list	*target_arg;

	target_arg = *args_list;
	while (target_arg->next)
		target_arg = target_arg->next;
	target_arg->separator = 1;
}

int	ft_split_char_separator(
	t_data_split **data, t_args_list **args_list, char *input, char separator)
{
	char	*tmp;

	(*data)->tmp[(*data)->i - (*data)->start] = '\0';
	tmp = ft_include_var(*data, (*data)->tmp);
	if (!tmp)
		return (0);
	if (!(*data)->space && (*data)->tmp[0])
	{
		if (!ft_join_args(args_list, tmp))
		{
			free(tmp);
			return (0);
		}
		(*data)->tmp[0] = '\0';
	}
	else if ((*data)->tmp[0] && !ft_one_split(data, args_list, input, tmp) && (*data)->tmp[0])
	{
		free(tmp);
		return (0);
	}
	(*data)->tmp[0] = separator;
	(*data)->tmp[1] = '\0';
	if (!ft_one_split(data, args_list, input, (*data)->tmp))
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	ft_set_type_separator(args_list);
	(*data)->i++;
	while (ft_isspace(input[(*data)->i]))
		(*data)->i++;
	(*data)->space = 1;
	(*data)->start = (*data)->i;
	(*data)->tmp[0] = '\0';
	return (1);
}

static
void	ft_set_string_separator(t_data_split *data, char *separator)
{
	data->tmp[0] = separator[0];
	data->tmp[1] = separator[1];
	data->tmp[2] = '\0';
}

int	ft_split_string_separator(
	t_data_split **data, t_args_list **args_list, char *input, char *separator)
{
	char	*tmp;

	(*data)->tmp[(*data)->i - (*data)->start] = '\0';
	tmp = ft_include_var(*data, (*data)->tmp);
	if (!tmp)
		return (0);
	if (!(*data)->space && (*data)->tmp[0])
	{
		if (!ft_join_args(args_list, tmp))
		{
			free(tmp);
			return (0);
		}
		(*data)->tmp[0] = '\0';
	}
	else if ((*data)->tmp[0] && !ft_one_split(data, args_list, input, tmp))
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	ft_set_string_separator(*data, separator);
	if (!ft_one_split(data, args_list, input, (*data)->tmp))
		return (0);
	ft_set_type_separator(args_list);
	(*data)->i += 2;
	while (ft_isspace(input[(*data)->i]))
		(*data)->i++;
	(*data)->space = 1;
	(*data)->start = (*data)->i;
	(*data)->tmp[0] = '\0';
	return (1);
}
