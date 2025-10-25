/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:47:44 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/19 15:33:08 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	**texture_map_alloc(int height, int width)
{
	int	**texture;
	int		i;

	texture = malloc(sizeof(unsigned int *) * (height));
	if (!texture)
		return (NULL);
	i = 0;
	while (i < height)
	{
		texture[i] = malloc(sizeof(unsigned int) * (width));
		if (!texture[i])
			return (free_double_array_error(texture, i), NULL);
		i++;
	}
	return (texture);
}

unsigned int	**extract_texture(int fd, t_vec2 dimension, char **tab_color)
{
	unsigned int	    **texture;
	char				*buffer;
	char				*tmp;
	t_vec2				var;
	
	texture = texture_map_alloc(dimension.v, dimension.u);
	if (!texture)
		return (NULL);
	var.v = -1;
	while (++var.v < dimension.v)
	{
		var.u = -1;
		buffer = get_next_line(fd);
		tmp = buffer;
		buffer = buffer + 1;
		while (++var.u < dimension.u)
		{
			texture[var.v][var.u] = search_color(buffer, tab_color);
			buffer = buffer + 2;
		}
		free(tmp);
	}
	return (texture);
}

unsigned int	**get_texture(char *file, t_objet *obj)
{
	int 			fd;
	unsigned int	**texture;
	char			**tab_color;
    char			*buffer;
	
	if (!file)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("open failed\n"), NULL);
	free(file);
	buffer = get_next_line(fd);
	obj->mat.texture_dimnesion = get_texture_dimension(fd);
	tab_color = get_color_tab(fd);
	if (!tab_color)
		return (NULL);
    texture = extract_texture(fd, obj->mat.texture_dimnesion, tab_color);
	if (!texture)
		return (free_double_array(tab_color), NULL);
	close(fd);
    return (texture);
}
