/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:38:26 by amedenec          #+#    #+#             */
/*   Updated: 2025/09/03 05:02:00 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	prep_list(t_liste **list)
{
	t_liste	*last_node;
	t_liste	*clean_node;
	int		i;
	int		j;
	char	*buf;

	last_node = give_last_node(*list);
	buf = malloc (BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_liste));
	if (!clean_node || !buf)
		return ;
	i = 0;
	j = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		i++;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		buf[j++] = last_node->str_buf[i];
	buf[j] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	free_list(list, clean_node, buf);
}

void	append(t_liste **list, char *buf)
{
	t_liste	*new_node;
	t_liste	*last_node;

	last_node = give_last_node(*list);
	new_node = malloc(sizeof(t_liste));
	if (!new_node)
		return ;
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
}

void	create_list(t_liste **list, int fd)
{
	int		char_read;
	char	*buf;

	while (!line_detected(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read)
		{
			free((buf));
			return ;
		}
		buf[char_read] = '\0';
		append(list, buf);
	}
}

char	*get_line(t_liste *list)
{
	int		len;
	char	*line;

	if (!list)
		return (NULL);
	len = count_line_gnl(list);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	copy_line(list, line);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_liste	*list = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(&list, fd);
	if (!list)
		return (NULL);
	next_line = get_line(list);
	prep_list(&list);
	return (next_line);
}

/*int	main(void)
{
	int	fd;

	fd = open("lala", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return (0);
}*/
