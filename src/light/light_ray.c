/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:11:00 by amedenec          #+#    #+#             */
/*   Updated: 2025/10/28 12:36:23 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_boolean	shadow_ray(t_mini *mini, t_vec3 ray_direction, double t)
{
	t_vec3		secondary_ray;
	t_vec3		p_intersect;
	t_boolean	result;

	p_intersect = vec_add(mini->sc.cam[mini->cam_lock].pos,
			vec_scale(ray_direction, t));
	secondary_ray = vec_substact(mini->sc.light[1].pos, p_intersect);
	result = is_intersect(mini, vec_normalize(secondary_ray), p_intersect);
	return (result);
}

t_boolean	is_hard_shadow(t_color c)
{
	if (c.r + c.g + c.b == 0)
		return (true);
	return (false);
}

t_color	light_ray(t_mini *mini, t_vec3 ray_dir, double t, t_objet obj)
{
	t_color	diffuse_direct;
	t_color	ambiant;
	t_color	spec;
	t_color	final;

	if (obj.type == sp)
		diffuse_direct = light_sp(mini, obj, ray_dir, t);
	else if (obj.type == pl)
		diffuse_direct = light_pl(mini, obj, ray_dir, t);
	else if (obj.type == cy)
		diffuse_direct = light_cy(mini, obj, ray_dir, t);
	else 
		diffuse_direct = light_tr(mini, obj, ray_dir, t);
	if (!is_hard_shadow(diffuse_direct))
		spec = specular(mini, obj, ray_dir, t);
	else
		spec = (t_color){0, 0, 0, 0};
	ambiant = apply_ambiant(mini, obj.color);
	final = mix_colors(diffuse_direct, ambiant);
	//final = mix_layer(final, spec);
	return (final);
}
