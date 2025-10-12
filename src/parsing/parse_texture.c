/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:22:24 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/12 15:37:18 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_boolean	is_digit_str(char *str)
{
	while (ft_isdigit(*str))
		str++;
	if (*str == 0)
		return (true);
	return (false);
}

t_boolean	is_on_xpm_pixel_info(char *str)
{
	if (ft_strncmp(str, "/* pixels */", 13) == 0)
		return (true);
	return (false);
}

char	**get_texture_dimension(int fd)
{
	char	*buffer;

	buffer = get_next_line(fd);
	while (!is_only_digit(buffer))
	{
		free(buffer);
		buffer = get_next_line(fd);
	}
	return (buffer);
}	

char	*go_to_pixel_info(int fd)
{
	char	*buffer;
	
	buffer = get_next_line(fd);
	while (!is_on_xpm_pixel_info(buffer))
	{
		free(buffer);
		buffer = get_next_line(fd);
	}
	free(buffer);
	buffer = get_next_line(fd);
	return (buffer);
}

char	**extract_texture(char *info_dimension, int fd)
{
	char	**texture;
	char	*buffer;
	t_vec2	var;
	int		width;
	int		height;
	
	var.u = 0;
	var.v = 0;
	width = __atoi_double(&info_dimension);
	height = __atoi_double(&info_dimension);
	texture = texture_map_alloc(height, width);
	if (!texture)
		return (NULL);
	buffer = go_to_pixel_info(fd);
	var.v = -1;
	while (++var.v > height)
	{
		var.u = -1;
		while (++var.u > width)
		{

		}
	}
	return (texture);
}

char	**texture_map_alloc(int height, int width)
{
	char	**texture;
	int		i;

	texture = malloc(sizeof(char *) * (height + 1));
	if (!texture)
		return (NULL);
	i = 0;
	while (i < width)
	{
		texture[i] = malloc(sizeof(char) * (width + 1));
		if (!texture[i])
			return (free_double_array_error(texture, i), NULL);
		i++;
	}
	return (texture);
}
char	**get_texture(char *file)
{
	int 	fd;
	char	**texture;
	char	*buffer;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	buffer = get_texture_dimension(fd);
	texture = extract_texture(buffer, fd);
	if (!texture)
		return (NULL);
	close(fd);
	return (texture);
}
