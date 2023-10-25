/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:00:58 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:25:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

static char	*ft_init(size_t start, size_t len, size_t s_len, size_t *new_len)
{
	if (start >= s_len)
		*new_len = 0;
	else
		*new_len = s_len - start;
	if (*new_len > len)
		*new_len = len;
	return (malloc(sizeof(char) * (*new_len + 1)));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			new_len;
	char			*res;

	if (!s)
		return (NULL);
	i = 0;
	res = ft_init((size_t)start, len, ft_strlen(s), &new_len);
	if (!res)
		return (NULL);
	while (new_len && len > 0 && s[start + i])
	{
		res[i] = s[start + i];
		i++;
		len--;
	}
	res[i] = '\0';
	return (res);
}
/*
#include <stdio.h>
int	main(void)
{
	//char	*str = "hola\0";
	printf("'%s'\n", ft_substr(NULL, 429467, 1844674407370));
	return (0);
}
*/
