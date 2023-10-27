/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:14:26 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/27 17:57:48 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int			ft_add_arg_to_list(t_args_list **cmd_split, char *tmp)
{
	t_args_list	*target_arg;

	if (!*cmd_split)
	{
		*cmd_split = ft_new_args_list(tmp);
		if (!*cmd_split)
			return (0);
		return (1);
	}
	target_arg = *cmd_split;
	while (target_arg->next)
		target_arg = target_arg->next;
	target_arg->next = ft_new_args_list(tmp);
	if (!target_arg->next)
		return (0);
	return (1);
}

static
size_t	ft_split_from_quotes(t_args_list **cmd_split, char *str_before, char *str_after)
{
	char	*tmp;
	size_t	len;

	if (str_before[0] && !ft_add_arg_to_list(cmd_split, str_before))
		return (0);
	tmp = ft_get_with_quotes(str_after);
	ft_printf("res btw q |%s|\n", tmp);
	if (!tmp)
		return (0);
	if (!ft_add_arg_to_list(cmd_split, tmp))
	{
		free(tmp);
		return (0);
	}
	len = ft_strlen(tmp);
	free(tmp);
	return (len + 2);
}

static
size_t	ft_join_from_quotes(t_args_list **cmd_split, char *str_before, char *str_after)
{
	char	*tmp;
	char	*res;
	size_t	len;

	tmp = ft_get_with_quotes(str_after);
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
char		**ft_args_list_to_str_split(t_args_list **cmd_split)
{
	t_args_list	*target;
	size_t		i;
	char		**res;

	target = *cmd_split;
	i = 0;
	while (target)
	{
		target = target->next;
		i++;
	}
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	target = *cmd_split;
	while (target)
	{
		ft_printf("args[%d]: [%s]\n", i, target->arg);
		res[i] = target->arg;
		target = target->next;
		i++;
	}
	res[i] = NULL;
	i = 0;
	return (res);
}

static
t_args_list	*ft_pre_split_args(char *input, size_t len)
{
	char		*tmp;
	size_t		i;
	size_t		start;
	t_args_list	*args_list;

	args_list = NULL;
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (ft_isspace(input[i]))
			i++;
	start = i;
	while (input[i])
	{
		if (ft_isspace(input[i]))
		{
			tmp[i - start] = '\0';
			//ft_printf("i - space = %d\n", i - start);
			if (!ft_add_arg_to_list(&args_list, tmp))
			{
				ft_free_args_list(&args_list);
				free(tmp);
				return (NULL);
			}
			while (ft_isspace(input[i]))
				i++;
			start = i;
		}
		else if ((input[i] == '\'' || input[i] == '"') && ft_has_endof_quotes(&input[i], input[i]))
		{
			tmp[i - start] = '\0';
			ft_printf("i - space = %d\n", i - start);
			ft_printf("tmp |%s|\n", tmp);
			ft_printf("rest |%s|\n", &input[i]); 
			if (start && ft_isspace(input[i - 1]))
				start = ft_split_from_quotes(&args_list, tmp, &input[i]);
			else
				start = ft_join_from_quotes(&args_list, tmp, &input[i]);
			ft_printf("after |%s|\n", &input[i + start]); 
			if (!start)
			{
				ft_free_args_list(&args_list);
				free(tmp);
				return (NULL);
			}
			i += start;
			while (input[i] && ft_isspace(input[i]))
				i++;
			ft_printf("after quotes |%s|\n", &input[i]); // echo "test" test2 test3 " 'test4' test5
			start = i;
		}
		else
		{
			tmp[i - start] = input[i];
			i++;
		}
	}
	tmp[i - start] = '\0';
	if (tmp[0])
	{
		if (!ft_add_arg_to_list(&args_list, tmp))
		{
			ft_free_args_list(&args_list);
			free(tmp);
			return (NULL);
		}
	}
	free(tmp);
	return (args_list);
}

char		**ft_split_args(char *input)
{
	char		**res;
	size_t		len;
	t_args_list	*args_list;

	len = ft_strlen(input);
	if (!ft_memchr(input, '"', len) && !ft_memchr(input, '\'', len))
		return (ft_split(input, ' '));
	args_list = ft_pre_split_args(input, len);
	res = ft_args_list_to_str_split(&args_list);
	ft_free_args_list(&args_list);
	if (!res)
		return (NULL);
	return (res);
}
