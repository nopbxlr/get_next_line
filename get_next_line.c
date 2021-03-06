/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctherin <ctherin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:56:01 by ctherin           #+#    #+#             */
/*   Updated: 2022/06/17 17:19:56 by ctherin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

char	*ft_clear(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

void	ft_terminate(char *buf, int rd_len)
{
	buf[rd_len] = EOF_CHAR;
	buf[rd_len + 1] = '\0';
}

char	*ft_add_data(char *tmp, int fd)
{
	char	*new;
	char	*buf;
	int		rd_len;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	rd_len = read(fd, buf, BUFFER_SIZE);
	if (rd_len == -1)
	{
		free(buf);
		return (NULL);
	}
	buf[rd_len] = '\0';
	if (rd_len < BUFFER_SIZE)
		ft_terminate(buf, rd_len);
	if (tmp)
	{
		new = ft_strjoin(tmp, buf);
		free(buf);
		free(tmp);
	}
	else
		new = buf;
	return (new);
}

char	*ft_get_line(char *persistent, int *ln_end)
{
	if (persistent[--*ln_end] == EOF_CHAR)
	{
		persistent[*ln_end] = '\0';
		if (*ln_end > 0)
			return (ft_substr(persistent, 0, *ln_end + 1));
		else
			return (NULL);
	}
	else
		return (ft_substr(persistent, 0, *ln_end + 1));
}

char	*get_next_line(int fd)
{
	static char	*persistent;
	char		*ln;
	char		*tmp;
	int			ln_end;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ln_end = ft_has_ending(persistent);
	while (ln_end == 0)
	{
		persistent = ft_add_data(persistent, fd);
		if (!persistent)
			return (NULL);
		ln_end = ft_has_ending(persistent);
	}
	tmp = persistent;
	ln = ft_get_line(persistent, &ln_end);
	if (!ln)
		return (ft_clear(&persistent));
	persistent = ft_strdup((char *)(persistent + ln_end + 1));
	free(tmp);
	if (!persistent)
		return (NULL);
	return (ln);
}
