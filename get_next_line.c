/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctherin <ctherin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:56:01 by ctherin           #+#    #+#             */
/*   Updated: 2022/06/13 23:38:46 by ctherin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

void	ft_eof(char	*s)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (!s[i])
			s[i] = 0xFF;
		i++;
	}
}

char	*ft_add_data(char *tmp, int fd)
{
	char	*new;
	char	*buf;
	size_t	rd_len;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	rd_len = read(fd, buf, BUFFER_SIZE);
	ft_eof(buf);
	buf[rd_len] = '\0';
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

char	*get_next_line(int fd)
{
	static char	*persistent;
	char		*ln;
	char		*tmp;
	size_t		ln_end;

	ln_end = ft_has_ending(persistent);
	while (!ln_end)
	{
		persistent = ft_add_data(persistent, fd);
		ln_end = ft_has_ending(persistent);
	}
	tmp = persistent;
	ln = ft_substr(persistent, 0, ln_end + 1);
	persistent = ft_strdup((char *)(persistent + ln_end + 1));
	free(tmp);
	return (ln);
}

/*#include<stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
int main()
{
	int fd = open("test.txt", O_RDONLY);
	for (int i = 0; i < 10; i++)
		printf("%s", get_next_line(fd));
	return 0;
}*/
