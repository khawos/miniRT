/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:08:17 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/12 16:21:52 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_boolean	shadow_ray(t_mini *mini, t_ray ray, double t, int light_index)
{
	t_boolean	result;
	t_ray		shadow_ray;

	shadow_ray.origin = vec_add(ray.origin,
			vec_scale(ray.current_dir, t * 0.98888));
	shadow_ray.current_dir = vec_substact
		(mini->sc.light[light_index].pos, shadow_ray.origin);
	result = is_intersect(mini, shadow_ray);
	return (result);
}

t_color	mix_light(t_color colors[LIGHT_MAX], t_mini *mini)
{
	int		i;
	t_color	color;

	i = 0;
	color = colors[0];
	while (i + 1 < mini->n_light && i + 1 < LIGHT_MAX)
	{
		color = color_add(color, colors[i + 1]);
		i++;
	}
	return (color);
}

static t_color	get_diffuse(t_mini *mini, t_ray *ray, t_objet obj,
	t_light_utils var)
{
	t_color	diffuse_direct;	

	if (obj.type == sp)
		diffuse_direct = light_sp(mini, obj, ray, var);
	else if (obj.type == pl)
	{
		diffuse_direct = light_pl(mini, obj, ray, var);
	}
	else if (obj.type == cy)
		diffuse_direct = light_cy(mini, obj, ray, var);
	else
		diffuse_direct = light_tr(mini, obj, ray, var);
	return (diffuse_direct);
}

t_color	handle_light(t_mini *mini, t_ray *ray, t_objet obj, t_light_utils *v)
{
	t_color	diff;
	t_color	spec;

	diff = get_diffuse(mini, ray, obj, *v);
	if (is_hard_shadow(diff))
		spec = (t_color){0, 0, 0};
	else
		spec = specular(mini, obj, ray, *v);
	return (mix_layer(diff, spec));
}

t_color	light_ray(t_mini *mini, t_ray *ray, t_objet obj)
{
	t_light_utils	v;
	t_color			color_obj;

	v.ambiant = color_scalar(mini->sc.ambiant.color, mini->sc.ambiant.ratio);
	v.light_colors = malloc(sizeof(t_color) * mini->n_light);
	if (!v.light_colors)
		return (ray->t = -1, (t_color){0, 0, 0});
	v.normal = get_object_normals(mini, obj, ray);
	v.i = 0;
	while (v.i < mini->n_light && v.i < LIGHT_MAX)
	{
		v.light_colors[v.i] = handle_light(mini, ray, obj, &v);
		v.i++;
	}
	color_obj = get_color_from_map(obj,
			vec_add(ray->origin, vec_scale(ray->current_dir, ray->t)), v.normal.geometric);
	v.ambiant = color_multiplie(v.ambiant, color_obj);
	ray->color = color_add(v.ambiant, mix_light(v.light_colors, mini));
	free(v.light_colors);
	v.final = reflection(mini, ray, obj, v.normal);
	if (ray->t == -1)
		return ((t_color){0, 0, 0});
	return (v.final);
}
