/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:15:02 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/31 18:01:36 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
size_t	ft_join_from_quotes(t_args_list **cmd_split, char *str_before, char *str_after)
{
	char	*tmp;
	char	*res;
	size_t	len;

	tmp = ft_between_quotes(str_after);
	if (!tmp)
		return (0);
	res = ft_strjoin(str_before, tmp);
	if (!res)
	{
		free(tmp);
		return (0);
	}
	if (!ft_add_arg_to_list(cmd_split, res))
	{
		free(tmp);
		return (0);
	}
	len = ft_strlen(tmp);
	free(tmp);
	return (len + 2);
}

static
int			ft_split_from_space(t_args_list **args_list, char *input, char *tmp)
{
	tmp[i - start] = '\0';
	if (!ft_add_arg_to_list(&args_list, tmp))
		return (ft_exit_split_args(&args_list, &tmp));
	while (ft_isspace(input[i]))
		i++;
	start = i;
}

static
int			ft_init_split_args(t_args_list **args_list, char **tmp, size_t len, size_t *i)
{
	*args_list = NULL;
	*tmp = malloc(sizeof(char) * (len + 1));
	if (!(*tmp))
		return (0);
	*i = 0;
	return (1);
}

static
void		*ft_exit_split_args(t_args_list **args_list, char **tmp)
{
	ft_free_args_list(args_list);
	free(*tmp);
	return (NULL);
}

static
void		ft_finish_split_args(t_args_list **args_list, char *tmp, size_t i, size_t start)
{
	tmp[i - start] = '\0';
	if (tmp[0])
	{
		if (!ft_add_arg_to_list(args_list, tmp))
		{
			ft_free_args_list(args_list);
			*args_list = NULL;
		}
	}
	free(tmp);
}

t_args_list	*ft_input_to_args_list(char *input, size_t len)
{
	char		*tmp;
	size_t		i;
	size_t		start;
	t_args_list	*args_list;

	if (!ft_init_split_args(&args_list, &tmp, len, &i))
		return (NULL);
	while (ft_isspace(input[i]))
			i++;
	start = i;
	while (input[i])
	{
		if (ft_isspace(input[i]))
		{
			tmp[i - start] = '\0';
			if (!ft_add_arg_to_list(&args_list, tmp))
				return (ft_exit_split_args(&args_list, &tmp));
			while (ft_isspace(input[i]))
				i++;
			start = i;
		}
		else if ((input[i] == '\'' || input[i] == '"') && ft_has_endof_quotes(&input[i], input[i]))
		{
			tmp[i - start] = '\0';
			if (start && ft_isspace(input[i - 1]))
				start = ft_split_from_quotes(&args_list, tmp, &input[i]);
			else
				start = ft_join_from_quotes(&args_list, tmp, &input[i]);
			if (!start)
				return (ft_exit_split_args(&args_list, &tmp));
			i += start;
			while (ft_isspace(input[i]))
				i++;
			start = i;
		}
		else
		{
			tmp[i - start] = input[i];
			i++;
		}
	}
	ft_finish_split_args(&args_list, tmp, i, start);
	return (args_list);
}
