/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_material.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:11:44 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/12 13:15:06 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_boolean	get_albedo(t_objet *obj, char *buffer)
{
	char	*str;

	str = ft_strnstr(buffer, "albedo=", ft_strlen(buffer));
	if (str)
	{
		obj->mat.albedo.map = get_texture(get_texture_path(str + 8),
				&obj->mat.albedo);
		if (!obj->mat.albedo.map)
			return (false);
		ft_printf("\033[1;32mAlbedo ok\033[0m\n");
	}
	return (true);
}

t_boolean	get_normal(t_objet *obj, char *buffer)
{
	char	*str;

	str = ft_strnstr(buffer, "normal=", ft_strlen(buffer));
	if (str)
	{
		obj->mat.normal.map = get_texture(get_texture_path(str + 8),
				&obj->mat.normal);
		if (!obj->mat.normal.map)
			return (free_double_array_error((void **)obj->mat.albedo.map,
					obj->mat.albedo.size.v), false);
		ft_printf("\033[1;32mNormal ok\033[0m\n");
	}
	return (true);
}

t_boolean	get_roughness(t_objet *obj, char *buffer)
{
	char	*str;

	str = ft_strnstr(buffer, "roughness=", ft_strlen(buffer));
	if (str)
	{
		obj->mat.roughness.map = get_texture(get_texture_path(str + 11),
				&obj->mat.roughness);
		if (!obj->mat.roughness.map)
			return (free_double_array_error((void **)obj->mat.albedo.map,
					obj->mat.albedo.size.v)
				, free_double_array_error((void **)obj->mat.normal.map,
					obj->mat.normal.size.v), false);
		ft_printf("\033[1;32mRoughness ok\033[0m\n", obj->mat.roughness.size);
	}
	return (true);
}

t_boolean	get_material(t_objet *obj, char *buffer)
{
	obj->mat.roughness.map = NULL;
	obj->mat.albedo.map = NULL;
	obj->mat.normal.map = NULL;
	if (!get_albedo(obj, buffer))
		return (false);
	if (!get_normal(obj, buffer))
		return (obj->mat.albedo.map = NULL, false);
	if (!get_roughness(obj, buffer))
		return (obj->mat.albedo.map = NULL, obj->mat.normal.map = NULL, false);
	return (true);
}
