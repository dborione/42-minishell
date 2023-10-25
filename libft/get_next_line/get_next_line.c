/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:04:04 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/06/01 10:13:24 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_clear(char *str1, char *str2)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (NULL);
}

static char	*just_first_line(char *text)
{
	char	*res_line;
	int		len;
	int		i;

	if (!text)
		return (NULL);
	len = 0;
	i = 0;
	while (text[len] && text[len] != '\n')
		len++;
	if (text[len] == '\n')
		len++;
	res_line = malloc(sizeof(char) * (len + 1));
	if (!res_line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res_line[i] = text[i];
		i++;
	}
	res_line[len] = '\0';
	return (res_line);
}

static char	*get_next_lines(char *previous_ls, char *target_l)
{
	int	p_len;
	int	t_len;

	p_len = ft_strlen(previous_ls);
	t_len = ft_strlen(target_l);
	if (p_len == 0 || t_len == 0 || p_len == t_len)
		return (NULL);
	return (ft_strdup_gnl(&previous_ls[t_len]));
}

static char	*get_next_from_previous(int fd, char *previous_ls)
{
	char	*buffer;
	char	*target_l;
	int		r_len;

	target_l = ft_strdup_gnl(previous_ls);
	if (!target_l && previous_ls)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_clear(target_l, NULL));
	r_len = 1;
	while (!ft_strchr_gnl(target_l, '\n') && r_len)
	{
		r_len = read(fd, buffer, BUFFER_SIZE);
		if (r_len == -1)
		{
			return (ft_clear(buffer, target_l));
		}
		buffer[r_len] = '\0';
		target_l = ft_strjoin_gnl(target_l, buffer);
		if (!target_l)
			return (ft_clear(buffer, NULL));
	}
	ft_clear(buffer, NULL);
	return (target_l);
}

char	*get_next_line(int fd)
{
	char		*target_l;
	char		*tmp;
	static char	*previous_ls;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (previous_ls && !previous_ls[0])
		ft_clear(previous_ls, NULL);
	tmp = get_next_from_previous(fd, previous_ls);
	if (!tmp || (!tmp[0] && !previous_ls))
	{
		ft_clear(tmp, previous_ls);
		previous_ls = NULL;
		return (NULL);
	}
	target_l = just_first_line(tmp);
	ft_clear(previous_ls, NULL);
	previous_ls = get_next_lines(tmp, target_l);
	ft_clear(tmp, NULL);
	return (target_l);
}
