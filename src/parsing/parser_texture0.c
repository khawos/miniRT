/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:47:44 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/12 13:08:51 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	**texture_map_alloc(int height, int width)
{
	unsigned int	**texture;
	int				i;

	texture = malloc(sizeof(unsigned int *) * (height + 1));
	if (!texture)
		return (NULL);
	i = 0;
	while (i < height)
	{
		texture[i] = malloc(sizeof(unsigned int) * (width));
		if (!texture[i])
			return (free_double_array_error((void **)texture, i), NULL);
		i++;
	}
	texture[i] = NULL;
	return (texture);
}

unsigned int	**extract_texture(int fd, t_vec2 dimension, char **tab_color, unsigned int nb_char_to_compare)
{
	unsigned int		**texture;
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
			texture[var.v][var.u] = search_color(buffer, tab_color, nb_char_to_compare);
			buffer = buffer + nb_char_to_compare;
		}
		free(tmp);
	}
	return (texture);
}

unsigned int	**get_texture(char *file, t_t_map *map)
{
	int				fd;
	unsigned int	**texture;
	char			**tab_color;
	unsigned int	nb_char_to_compare;

	if (!file)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_printf("failed to open %s\n", file), free(file), NULL);
	free(file);
	map->size = get_texture_dimension(fd, &nb_char_to_compare);
	printf("nb : %u\n", nb_char_to_compare);
	tab_color = get_color_tab(fd);
	if (!tab_color)
		return (clear_gnl(fd), NULL);
	texture = extract_texture(fd, map->size, tab_color, nb_char_to_compare);
	if (!texture)
		return (clear_gnl(fd), free_double_array(tab_color), NULL);
	free_double_array(tab_color);
	clear_gnl(fd);
	close(fd);
	return (texture);
}
