/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:02:24 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/08 17:40:26 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

typedef struct s_specular
{
	t_color	specular;
	t_vec3	halfway;
	t_vec3	to_cam;
	t_vec3	intersect;
	t_vec3	to_light;
	t_vec3	normal;
}				t_specular;

void	specular_util(t_specular *var, t_objet obj, double is_cap, double t)
{
	t_vec3	base;

	(void)base;
	if (sp == obj.type)
		var->normal = vec_normalize(vec_substact(var->intersect, obj.pos));
	if (pl == obj.type)
		var->normal = obj.vec_dir;
	else if (cy == obj.type && t != is_cap)
	{
		base = vec_substact(obj.pos, vec_scale(obj.vec_dir, obj.height / 2));
		var->normal = vec_normalize(vec_substact(var->intersect,
					vec_add(base, vec_scale(obj.vec_dir,
							vec_dot(vec_substact(var->intersect, base),
								obj.vec_dir)))));
	}
	else if (cy == obj.type && t == is_cap)
		var->normal = obj.vec_dir;
}

t_color	specular(t_mini *mini, t_objet obj, t_vec3 ray_dir, double t)
{
	t_specular	var;
	t_color		light_color;
	double		dot;
	double		is_cap;

	if (obj.type == cy)
		is_cap = intersect_cap(mini->sc.cam[0].pos, ray_dir, obj);
	var.intersect = vec_add(mini->sc.cam[0].pos, vec_scale(ray_dir, t));
	specular_util(&var, obj, is_cap, t);
	var.to_light = vec_normalize(vec_substact(mini->sc.light[1].pos,
				var.intersect));
	light_color = color_scalar(mini->sc.light[1].color,
			mini->sc.light[1].ratio);
	var.to_cam = vec_normalize(vec_substact(mini->sc.cam[0].pos,
				var.intersect));
	var.halfway = vec_normalize(vec_add(var.to_light, var.to_cam));
	dot = vec_dot(var.normal, var.halfway);
	var.specular = color_scalar(light_color, pow(fmax(dot, 0), 35));
	return (var.specular);
}
