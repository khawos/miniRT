/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_material.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:11:44 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/25 20:23:08 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_boolean get_material(t_objet *obj, char *buffer)
{
	char	*str;

	obj->mat.albedo.map = NULL;
	obj->mat.normal.map = NULL;
	str = ft_strnstr(buffer, "albedo=", ft_strlen(buffer));
	if (str)
	{
		obj->mat.albedo.map = get_texture(get_texture_path(str + 8), &obj->mat.albedo);
		if (!obj->mat.albedo.map)
			return (false);
		printf("albedo ok\n");
	}
	str = ft_strnstr(buffer, "normal=", ft_strlen(buffer));
	if (str)
	{
		obj->mat.normal.map = get_texture(get_texture_path(str + 8),  &obj->mat.normal);
		if (!obj->mat.normal.map)
			return (free_double_array_error(obj->mat.albedo.map,
				obj->mat.normal.size.v), false);
		printf("normal ok\n");
	}
	return (true);
}