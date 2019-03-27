/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 11:31:09 by sipatry           #+#    #+#             */
/*   Updated: 2018/11/30 13:57:31 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchrcpy(char *tmp, char s)
{
	char	*dst;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (tmp[j] != s)
		j++;
	if (!(dst = (char*)malloc(sizeof(char) * j + 1)))
		return (0);
	while (i < j)
	{
		dst[i] = tmp[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char		*ft_line(char **line, char *tmp)
{
	if (ft_strchr(tmp, '\n') == 0)
	{
		if (!(*line = ft_strdup((const char*)tmp)))
			return (0);
	}
	else
	{
		if (!(*line = ft_strchrcpy(tmp, '\n')))
			return (0);
	}
	return (*line);
}

char		*push_tmp(char *tmp)
{
	char	*tmp_free;
	char	*dest;

	tmp_free = tmp;
	while (*tmp != '\n' && *tmp != '\0')
		tmp++;
	if (*tmp == '\n')
		tmp++;
	if (!(dest = ft_strdup((const char*)tmp)))
		return (0);
	free(tmp_free);
	return (dest);
}

int			check_value(char *tmp, char *line, int res)
{
	if (*tmp == '\0')
		res = 0;
	if ((res == 0 && *tmp == '\0' && !line))
		return (0);
	else
		return (1);
}

int			get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	static char	*tmp[4864];
	char		*tmp_free;
	int			res;
	int			ret;

	if (fd < 0 || !line || !BUFF_SIZE || (read(fd, 0, 0)) == -1)
		return (-1);
	if (!tmp[fd])
		tmp[fd] = ft_strnew(1);
	else
		tmp[fd] = push_tmp(tmp[fd]);
	while (ft_strchr(tmp[fd], '\n') == 0 && (res = read(fd, buff, BUFF_SIZE)))
	{
		buff[res] = '\0';
		tmp_free = tmp[fd];
		tmp[fd] = ft_strjoin(tmp[fd], buff);
		free(tmp_free);
	}
	*line = (*tmp[fd]) ? ft_line(line, tmp[fd]) : NULL;
	ret = check_value(tmp[fd], *line, res);
	return (ret);
}
