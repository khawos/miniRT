/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:11:00 by amedenec          #+#    #+#             */
/*   Updated: 2025/10/29 13:48:45 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_normal	get_object_normals(t_mini *mini, t_objet obj, t_ray *ray)
{
	t_normal	normal;
	t_vec3		base_cy;
	t_vec3		p;
	
	p = vec_add(ray->origin, vec_scale(ray->dir, ray->t));
	if (obj.type == sp)
	{
		normal = get_normal_sp_from_map(mini, obj, ray);
		return (normal);
	}
	if (obj.type == tr)
	{
		normal.geometric = obj.normal;
		normal.texture = vec_create(0,0,0);
		return (normal);		
	}
	if (obj.type == pl)
	{
		normal.geometric = obj.vec_dir;
		normal.texture = vec_create(0,0,0);
		return (normal);
	}
	if (obj.type == cy && ray->t != intersect_cap(ray->origin, ray->dir, obj))
	{
		base_cy = vec_substact(obj.pos, vec_scale(obj.vec_dir, obj.height / 2));
		normal.geometric = vec_normalize(vec_substact(p,
			vec_add(base_cy, vec_scale(obj.vec_dir,
					vec_dot(vec_substact(p, base_cy), obj.vec_dir)))));
		normal.texture = vec_create(222, 0, 0);
		return (normal);
	}
	else
	{
		normal.geometric = obj.vec_dir;
		normal.texture = vec_create(222, 0, 0);
		return (normal);
	}
}

t_boolean	shadow_ray(t_mini *mini, t_ray ray, double t, int light_index)
{
	t_vec3		secondary_ray;
	t_vec3		p_intersect;
	t_boolean	result;

	p_intersect = vec_add(ray.origin,
			vec_scale(ray.dir, t));
	secondary_ray = vec_substact(mini->sc.light[light_index].pos, p_intersect);
	result = is_intersect(mini, vec_normalize(secondary_ray), p_intersect, light_index);
	return (result);
}

t_boolean	is_hard_shadow(t_color c)
{
	if (c.r + c.g + c.b == 0)
		return (true);
	return (false);
}

t_color	mix_light(t_color colors[LIGHT_MAX], t_mini *mini)
{
	int		i;
	t_color	color;
	
	i = 0;
	color = colors[0];
	while (i + 1 < mini->N_LIGHT && i + 1 < LIGHT_MAX)
	{
		color = color_add(color, colors[i + 1]);
		i++;
	}
	return(color);
}

t_color	light_ray(t_mini *mini, t_ray *ray, t_objet obj)
{
	t_color			diffuse_direct;
	t_color			ambiant;
	t_color			spec;
	t_color			colors[LIGHT_MAX];
	t_color			final;
	t_light_utils	var;
			
	var.i = 0;
	var.normal = get_object_normals(mini, obj, ray);
	while (var.i < mini->N_LIGHT && var.i < LIGHT_MAX)
	{
		if (obj.type == sp)
			diffuse_direct = light_sp(mini, obj, ray, var);
		else if (obj.type == pl)
			diffuse_direct = light_pl(mini, obj, ray, var);
		else if (obj.type == cy)
			diffuse_direct = light_cy(mini, obj, ray, var);
		else 
			diffuse_direct = light_tr(mini, obj, ray, var);
		if (!is_hard_shadow(diffuse_direct))
			spec = specular(mini, obj, ray, var); 
		else
			spec = (t_color){0, 0, 0, 0};
		ambiant = apply_ambiant(mini, diffuse_direct);
		colors[var.i] = color_add(diffuse_direct, ambiant);
		colors[var.i] = mix_layer(colors[var.i], spec);
		var.i++;
	}
	ray->color = mix_light(colors, mini);
	final = reflection(mini, ray, obj, var.normal);
	return (final);
}
