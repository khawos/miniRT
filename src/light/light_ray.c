/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:08:17 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/01 14:48:59 by amedenec         ###   ########.fr       */
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
	result = is_intersect(mini, vec_normalize(secondary_ray), p_intersect,
			light_index);
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

t_color	light_ray(t_mini *mini, t_ray *ray, t_objet obj)
{
	t_light_utils	var;

	var.light_colors = malloc(sizeof(t_color) * mini->N_LIGHT);
	if (!var.light_colors)
		return (ray->t = -1, (t_color){0, 0, 0});
	var.i = 0;
	var.normal = get_object_normals(mini, obj, ray);
	while (var.i < mini->N_LIGHT && var.i < LIGHT_MAX)
	{
		var.diffuse_direct = get_diffuse(mini, ray, obj, var);
		if (!is_hard_shadow(var.diffuse_direct))
			var.spec = specular(mini, obj, ray, var);
		else
			var.spec = (t_color){0, 0, 0};
		var.ambiant = apply_ambiant(mini, var.diffuse_direct);
		var.light_colors[var.i] = color_add(var.diffuse_direct, var.ambiant);
		var.light_colors[var.i] = mix_layer(var.light_colors[var.i], var.spec);
		var.i++;
	}
	ray->color = mix_light(var.light_colors, mini);
	free(var.light_colors);
	var.final = reflection(mini, ray, obj, var.normal);
	if (ray->t == -1)
		return ((t_color){0, 0, 0});
	return (var.final);
}
