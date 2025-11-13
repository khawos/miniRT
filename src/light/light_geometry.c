/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_geometry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:56:31 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/02 13:27:48 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	get_dot(t_objet obj, t_ray *ray, t_vec3 to_light, t_vec3 normal)
{
	double			dot;

	if (vec_get_norme(to_light) < obj.diameter / 2)
	{	
		if (vec_get_norme(vec_substact(ray->origin, obj.pos))
			< obj.diameter / 2)
			dot = 1;
		else
			dot = 0;
	}
	else
		dot = vec_dot(vec_normalize(normal), vec_normalize(to_light));
	if (dot < 0)
		dot = 0;
	return (dot);
}

t_color	light_sp(t_mini *mini, t_objet obj, t_ray *ray, t_light_utils utils)
{
	t_vec3			p;
	t_vec3			to_light;
	double			dot;
	t_var_texture	texture;
	t_vec3			normal;

	if (shadow_ray(mini, *ray, ray->t, utils.i))
		return ((t_color){0, 0, 0});
	if (is_null_vector(utils.normal.texture))
		normal = utils.normal.geometric;
	else
		normal = utils.normal.texture;
	if (shadow_ray(mini, *ray, ray->t, utils.i))
		return ((t_color){0, 0, 0});
	p = vec_add(ray->origin, vec_scale(ray->current_dir, ray->t));
	to_light = vec_substact(mini->sc.light[utils.i].pos, obj.pos);
	texture.color = get_color_from_map(obj, p);
	dot = get_dot(obj, ray, to_light, normal);
	return (color_scalar(color_multiplie(texture.color,
				color_scalar(mini->sc.light[utils.i].color,
					mini->sc.light[utils.i].ratio)), dot));
}

t_color	light_pl(t_mini *mini, t_objet obj, t_ray *ray, t_light_utils utils)
{
	t_vec3	p;
	t_vec3	to_light;
	double	dot;
	t_vec3	normal;

	if (is_null_vector(utils.normal.texture))
		normal = utils.normal.geometric;
	else
		normal = utils.normal.texture;
	if (shadow_ray(mini, *ray, ray->t, utils.i))
		return ((t_color){0, 0, 0});
	p = vec_add(ray->origin, vec_scale(ray->current_dir, ray->t));
	to_light = vec_substact(mini->sc.light[utils.i].pos, p);
	dot = fabs(vec_dot(normal, vec_normalize(to_light)));
	return (color_scalar(color_multiplie(obj.color,
				color_scalar(mini->sc.light[utils.i].color,
					mini->sc.light[utils.i].ratio)), dot));
}

t_color	light_tr(t_mini *mini, t_objet obj, t_ray *ray, t_light_utils utils)
{
	t_vec3	p;
	t_vec3	to_light;
	double	dot;

	if (shadow_ray(mini, *ray, ray->t, utils.i))
		return ((t_color){0, 0, 0});
	p = vec_add(ray->origin, vec_scale(ray->current_dir, ray->t));
	to_light = vec_substact(mini->sc.light[utils.i].pos, p);
	dot = fabs(vec_dot(obj.normal, vec_normalize(to_light)));
	return (color_scalar(color_multiplie(obj.color,
				color_scalar(mini->sc.light[utils.i].color,
					mini->sc.light[utils.i].ratio)), dot));
}
