/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:11:00 by amedenec          #+#    #+#             */
/*   Updated: 2025/10/30 15:38:03 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_boolean	shadow_ray(t_mini *mini, t_ray ray, double t, int light_index)
{
	t_vec3		secondary_ray;
	t_vec3		p_intersect;
	t_boolean	result;

	p_intersect = vec_add(ray.origin,
			vec_scale(ray.current_dir, t));
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

t_color	*compute_light_color(t_mini *mini, t_ray *ray, t_objet obj, t_light_utils *var)
{
	t_color			ambiant;
	t_color			spec;
	t_color			diffuse_direct;
	
	if (obj.type == sp)
		diffuse_direct = light_sp(mini, obj, ray, *var);
	else if (obj.type == pl)
		diffuse_direct = light_pl(mini, obj, ray, *var);
	else if (obj.type == cy)
		diffuse_direct = light_cy(mini, obj, ray, *var);
	else 
		diffuse_direct = light_tr(mini, obj, ray, *var);
	if (!is_hard_shadow(diffuse_direct))
		spec = specular(mini, obj, ray, *var); 
	else
		spec = (t_color){0, 0, 0, 0};
	ambiant = apply_ambiant(mini, diffuse_direct);
	var->light_colors[var->i] = color_add(diffuse_direct, ambiant);
	var->light_colors[var->i] = mix_layer(var->light_colors[var->i], spec);
	return (var->light_colors);
}

t_color	light_ray(t_mini *mini, t_ray *ray, t_objet obj)
{
	t_color			final;
	t_light_utils	var;
	t_color			ambiant;
	t_color			spec;
	t_color			diffuse_direct;	
	
	var.light_colors = malloc(sizeof(t_color) * mini->N_LIGHT);
	if (!var.light_colors)
		return (ray->t = -1, (t_color){0,0,0});
	var.i = 0;
	var.normal = get_object_normals(mini, obj, ray);
	while (var.i < mini->N_LIGHT && var.i < LIGHT_MAX)
	{
		//var.light_colors = compute_light_color(mini, ray, obj ,&var);
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
		var.light_colors[var.i] = color_add(diffuse_direct, ambiant);
		var.light_colors[var.i] = mix_layer(var.light_colors[var.i], spec);
		var.i++;
	}
	ray->color = mix_light(var.light_colors, mini);
	free(var.light_colors);
	final = reflection(mini, ray, obj, var.normal);
	if (ray->t == -1)
		return ((t_color){0,0,0});
	return (final);
}
