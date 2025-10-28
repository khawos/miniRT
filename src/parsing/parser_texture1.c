/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:07:44 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/28 12:25:44 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*get_texture_path(char *str)
{
	char	*path;

	path = NULL;
	while (*str != '"')
	{
		path = dynamic_copy(path, *str);
		if (!path)
			return (NULL);
		str++;
	}
	printf("texture path : %s\n", path);
	return (path);
}

char	**get_color_tab(int fd)
{
	char	**tab;
	char	*buffer;

	buffer = get_next_line(fd);
	tab = NULL;
	while (!is_on_xpm_pixel_info(buffer))
	{
		tab = realloc_add_to_tab(tab, buffer);
		if (!tab)
			return(free(buffer), NULL);
		buffer = get_next_line(fd);
	}
	return (tab);
}

unsigned int	search_color(char *buffer, char **tab_color)
{
	int				i;
	unsigned int	color;

	i = 0;
	while (tab_color[i])
	{
		if (ft_strncmp(buffer, tab_color[i] + 1, 2) == 0)
		{
			color = ft_atoi_base(tab_color[i] + 7, "0123456789ABCDEF");
			return (color);
		}
		i++;
	}
	return (0);
}