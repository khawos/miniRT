/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:07:44 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/19 15:28:40 by jbayonne         ###   ########.fr       */
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

t_boolean get_material(t_objet *obj, char *buffer)
{
	char	*str;

	obj->mat.albedo = NULL;
	str = ft_strnstr(buffer, "albedo=", ft_strlen(buffer));
	if (str)
	{
		obj->mat.albedo = get_texture(get_texture_path(str + 8));
		if (!obj->mat.albedo)
			return (false);
	}
	return (true);
}

char	**get_color_tab(int fd)
{
	char	**tab;
	char	*buffer;

	buffer = get_next_line(fd);
	tab = NULL;
	while (!is_on_xpm_pixel_info(buffer))
	{
		buffer = get_next_line(fd);
		tab = realloc_add_to_tab(tab, buffer);
		if (!tab)
			return(free(buffer), NULL);
	}
	return (tab);
}

unsigned int	search_color(char *buffer, char **tab_color)
{
	int	i;

	i = 0;
	while (tab_color[i])
	{
		if (ft_strncmp(buffer, tab_color[i] + 1, 2) == 0)
			return(ft_atoi_base(buffer, "0123456789ABCDEF"));
		i++;
	}
	return (0);
}