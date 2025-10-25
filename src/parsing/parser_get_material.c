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

	obj->mat.albedo = NULL;
	str = ft_strnstr(buffer, "albedo=", ft_strlen(buffer));
	if (str)
	{
		obj->mat.albedo = get_texture(get_texture_path(str + 8), obj);
		if (!obj->mat.albedo)
			return (false);
		printf("albedo ok\n");
	}
	str = ft_strnstr(buffer, "normal=", ft_strlen(buffer));
	if (str)
	{
		obj->mat.normal_map = get_texture(get_texture_path(str + 8), obj);
		if (!obj->mat.normal_map)
			return (free_double_array_error(obj->mat.albedo,
				obj->mat.texture_dimnesion.v), false);
		printf("normal ok\n");
	}
	return (true);
}