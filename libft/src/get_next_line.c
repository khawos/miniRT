/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:43:03 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/28 13:51:39 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

char	*ft_free(char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
		return (str);
	}
	else
	{
		str = NULL;
		return (str);
	}
}

static int	is_line(char *read, char *buffer)
{
	int	i;

	if (len(buffer) == 0 && len(read) != 0)
		return (1);
	i = 0;
	while (read[i])
	{
		if (read[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_search_line(char *buffer, char *next_line, ssize_t i, int fd)
{
	static char	*read[1000];

	next_line = 0;
	read[fd] = ft_read_init(buffer, read[fd], i);
	if (i < 0)
		return (ft_free(next_line), ft_free(read[fd]));
	if (!read[fd])
		return (ft_free(next_line));
	if (!is_line(read[fd], buffer))
	{
		if (len(read[fd]) == 0)
			read[fd] = ft_free(read[fd]);
		return (NULL);
	}
	else
		next_line = ft_next_line_init(read[fd]);
	if (!next_line)
		return (NULL);
	read[fd] = ft_read_update(read[fd], next_line);
	if (!read[fd])
		return (ft_free(next_line), ft_free(read[fd]));
	if (len(read[fd]) == 0)
		read[fd] = ft_free(read[fd]);
	return (next_line);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	char		*buffer;
	ssize_t		i;

	i = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (i != 0)
	{	
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 0)
		{
			ft_search_line(0, next_line, i, fd);
			return (ft_free(buffer));
		}
		buffer[i] = '\0';
		next_line = ft_search_line(buffer, next_line, i, fd);
		if (!(!next_line))
			return (ft_free(buffer), next_line);
		next_line = ft_free(next_line);
	}
	return (ft_free(buffer));
}