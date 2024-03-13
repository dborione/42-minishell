/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:44:23 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 13:35:57 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

static int	ft_starts_with(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_ends_with(char const *str, char const *set)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (str[i])
	{
		if (ft_starts_with(str[i], set))
			found++;
		i++;
	}
	if (found == i)
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		y;
	int		new_len;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	y = 0;
	new_len = 0;
	while (ft_starts_with(s1[i], set))
		i++;
	while (s1[i + new_len] && !ft_ends_with(&s1[i + new_len], set))
		new_len++;
	res = malloc(sizeof(char) * (new_len + 1));
	if (!res)
		return (NULL);
	while (s1[i] && y < new_len)
		res[y++] = s1[i++];
	res[y] = '\0';
	return (res);
}
/*
#include <stdio.h>

int	main(void)

{		
	char *s = "   \t  \n\n \t\t  \n\n\nHello \t  Please\n Trim me !\n   ";
	//char *n_res = "Hello \t  Please\n Trim me !";
	char *m_res = ft_strtrim(s, NULL); //" \n\t");
	
	//printf("s1 : '%s'\n", s);	
	//printf("res : '%s'\n", n_res);
	printf("res : '%s'\n", m_res);
	//if (!memcmp(m_res, s, ft_strlen(s)))
	//	printf("Aucun changement\n");
	//if (memcmp(m_res, n_res, ft_strlen(n_res)))
	//	printf("Mauvais resultat\n");
	//else
	//	printf("FONCTIONNEL\n");
	return (0);
}*/
