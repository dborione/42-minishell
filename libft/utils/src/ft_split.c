/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:42:46 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:25:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

static int	ft_count_el(const char *src, const char sep)
{
	int		i;
	int		in_sep;
	int		count;

	i = 0;
	in_sep = 0;
	count = 0;
	while (src[i])
	{
		if (src[i] != sep && !in_sep)
		{
			in_sep = 1;
			count++;
		}
		else if (src[i] == sep)
			in_sep = 0;
		i++;
	}
	return (count);
}

static char	*ft_next_el(char const *str, int start, int end)
{
	int		i;
	int		len;
	char	*dst;

	i = 0;
	len = end - start;
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	while (i < len)
	{
		dst[i] = str[i + start];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static int	ft_init(const char *str, char c, char ***res, int *i)
{
	*res = malloc(sizeof(char *) * (ft_count_el(str, c) + 1));
	if (!*res)
		return (0);
	i[0] = 0;
	i[1] = -1;
	i[2] = 0;
	return (1);
}

static char	**ft_free(char **res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

char	**ft_split(char const *str, char c)
{
	int		i[3];
	char	**res;

	if (!str || !ft_init(str, c, &res, i))
		return (NULL);
	while (i[2] < ft_count_el(str, c))
	{
		if (i[1] < 0 && str[i[0]] != c)
			i[1] = i[0];
		else if ((str[i[0]] == c || !str[i[0] + 1]) && i[1] >= 0)
		{
			if (!str[i[0] + 1] && str[i[0]] != c)
				i[0]++;
			res[i[2]] = ft_next_el(str, i[1], i[0]);
			if (!res[i[2]])
				return (ft_free(res));
			i[2]++;
			i[1] = -1;
		}
		i[0]++;
	}
	res[i[2]] = NULL;
	return (res);
}
/*
#include <stdio.h>

int	main(void)
{
	char	**array = ft_split(NULL, '1');//"split  ||this|for|me|||||!|", 0);
	int		i = 0;

	if (array)
	{
		while (array[i])
		{
			printf("'%s'\n", array[i]);
			i++;
		}
	}
	return (0);
}
*/
