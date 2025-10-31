/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:02:24 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/30 14:38:41 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_specular
{
	t_color	specular;
	t_vec3	halfway;
	t_vec3	to_cam;
	t_vec3	intersect;
	t_vec3	to_light;
	t_vec3	normal;
	t_vec3	up_world;
}				t_specular;

t_color	specular(t_mini *mini, t_objet obj, t_ray *ray, t_light_utils utils)
{
	t_specular	var;
	t_color		light_color;
	double		dot;
	double		spec;

	if (is_null_vector(utils.normal.texture))
		var.normal = utils.normal.geometric;
	else
		var.normal = utils.normal.texture;
	spec = 15;
	if (obj.spec != -1)
		spec = obj.spec;
	var.up_world = mini->up_world;
	var.intersect = vec_add(ray->origin, vec_scale(ray->current_dir, ray->t));
	var.to_light = vec_normalize(vec_substact(mini->sc.light[utils.i].pos,
				var.intersect));
	light_color = color_scalar(mini->sc.light[utils.i].color,
			mini->sc.light[utils.i].ratio);
	var.to_cam = vec_normalize(vec_substact(ray->origin,
				var.intersect));
	var.halfway = vec_normalize(vec_add(var.to_light, var.to_cam));
	dot = vec_dot(var.normal, var.halfway);
	var.specular = color_scalar(light_color, pow(fmax(dot, 0), get_roughness_from_map(obj, spec, vec_normalize(vec_substact(var.intersect, obj.pos)))));
	return (var.specular);
}
