/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:13:46 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/28 18:11:44 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	len(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_next_line_init(char *read)
{
	int		i;
	int		j;
	char	*next_line;

	i = 0;
	j = 0;
	while (read[i] != '\n' && read[i] != '\0')
		i++;
	next_line = malloc(sizeof(char) * (i + 2));
	if (!next_line)
		return (NULL);
	i = 0;
	while (read[i + j] != '\n' && read[i + j] != '\0')
	{
		next_line[j] = read[i + j];
		j++;
	}
	if (read[i + j] == '\n')
	{
		next_line[j] = '\n';
		j++;
	}
	next_line[j] = '\0';
	return (next_line);
}

static char	*ft_cpy(char *tmp, char *buffer, char *read)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (tmp != 0)
	{
		while (tmp[i])
		{
			read[i] = tmp[i];
			i++;
		}
	}
	while (buffer[j])
	{
		read[i + j] = buffer[j];
		j++;
	}
	read[i + j] = '\0';
	return (read);
}

char	*ft_read_update(char *read, char *next_line)
{
	char	*tmp;
	int		i;

	i = 1;
	if (len(read) - len(next_line) == 0)
		i = 2;
	tmp = malloc(sizeof(char) * (len(read) - len(next_line) + i));
	if (!tmp)
		return (ft_free(read));
	read += len(next_line);
	tmp = ft_cpy(0, read, tmp);
	read -= len(next_line);
	read = ft_free(read);
	return (tmp);
}

char	*ft_read_init(char *buffer, char *read, ssize_t i)
{
	char	*tmp;

	tmp = 0;
	if (i < 0)
	{
		read = NULL;
		return (read);
	}
	if (len(read))
		tmp = read;
	read = malloc(sizeof(char) * (len(buffer) + len(read) + 1));
	if (!read)
		return (NULL);
	read = ft_cpy(tmp, buffer, read);
	if (tmp != 0)
		tmp = ft_free(tmp);
	return (read);
}
