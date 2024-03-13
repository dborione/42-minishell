/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:42:46 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 14:15:18 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

static int	ft_tab_len(const char *ptr, char c)
{
	unsigned long	i;
	int				count;
	unsigned int	len;

	i = 0;
	count = 0;
	len = ft_strlen(ptr);
	while (i < len)
	{
		while (i < len && ptr[i] != c)
		{
			i++;
			if (ptr[i] == c || ptr[i] == '\0')
				count++;
		}
		i++;
	}
	return (count);
}

static char	**ft_empty_tab(char **tab)
{
	tab = malloc(sizeof(*tab));
	if (!tab)
		return (NULL);
	tab[0] = NULL;
	return (tab);
}

static char	**ft_free_tab(char **tab)
{
	int	x;

	x = 0;
	while (tab[x])
	{
		free(tab[x]);
		x++;
	}
	free(tab);
	return (NULL);
}

static char	**ft_fill_tab(char **tab, const char *s, char c, int x)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (i < ft_strlen(s))
	{
		while (s[i] && s[i] != c)
		{
			i++;
			if (s[i] == c || s[i] == '\0')
			{
				tab[x] = ft_substr(s, j, i - j);
				if (!tab[x])
					return (ft_free_tab(tab));
				x++;
				j = i;
			}
		}
		j++;
		i++;
	}
	tab[x] = NULL;
	return (tab);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		count;
	int		x;

	x = 0;
	if (!s)
		return (NULL);
	count = 0;
	tab = NULL;
	count = ft_tab_len(s, c);
	if (count == 0)
		return (ft_empty_tab(tab));
	tab = malloc(sizeof(*tab) * (count + 1));
	if (!tab)
		return (NULL);
	tab = ft_fill_tab(tab, s, c, x);
	if (!tab)
		return (ft_free_tab(tab));
	return (tab);
}
