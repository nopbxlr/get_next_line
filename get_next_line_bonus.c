/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctherin <ctherin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:56:01 by ctherin           #+#    #+#             */
/*   Updated: 2022/06/16 22:22:05 by ctherin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

char	*ft_clear(char **ptr, int fd)
{
	if (ptr[fd])
	{
		free(ptr[fd]);
		ptr[fd] = NULL;
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
	static char	*persistent[MAX_FD];
	char		*ln;
	char		*tmp;
	int			ln_end;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	ln_end = ft_has_ending(persistent[fd]);
	while (ln_end == 0)
	{
		persistent[fd] = ft_add_data(persistent[fd], fd);
		if (!persistent[fd])
			return (NULL);
		ln_end = ft_has_ending(persistent[fd]);
	}
	tmp = persistent[fd];
	ln = ft_get_line(persistent[fd], &ln_end);
	if (!ln)
		return (ft_clear(persistent, fd));
	persistent[fd] = ft_strdup((char *)(persistent[fd] + ln_end + 1));
	free(tmp);
	if (!persistent[fd])
		return (NULL);
	return (ln);
}

/*#include<stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
int main()
{
	int fd = open("test.txt", O_RDONLY);
	char *str;
	for (int i = 0; i < 15; i++)
	{
		str = get_next_line(fd);
		printf("ln %d, %s\n", i, str);
		free(str);
	}
	return 0;
}
*/