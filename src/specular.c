/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-27 14:02:24 by jbayonne          #+#    #+#             */
/*   Updated: 2025-09-27 14:02:24 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

typedef	struct s_specular
{
	t_color specular;
	t_vec3  halfway;
	t_vec3	to_cam;
	t_vec3  intersect;
	t_vec3  to_light;
	t_vec3  normal;
}				t_specular;

void	specular_util(t_specular *var, t_objet obj)
{
	t_vec3	base;

	(void)base;
	if (sp == obj.type)
		var->normal = vec_normalize(vec_substact(var->intersect, obj.pos));
	else if (pl == obj.type)
		var->normal = obj.vec_dir;
	else if (cy == obj.type && !obj.cap)
	{
		base = vec_substact(obj.pos, vec_scale(obj.vec_dir, obj.height / 2));
		var->normal = vec_normalize(vec_substact(var->intersect,
			vec_add(base, vec_scale(obj.vec_dir,
					vec_dot(vec_substact(var->intersect, base), obj.vec_dir)))));
	}
}

t_color specular_sp(t_mini *mini, t_objet obj, t_vec3 ray_dir, double t)
{
	t_specular	var;
	t_color		light_color;
	double		dot;

	specular_util(&var, obj);
	light_color = color_scalar(mini->sc.light[0].color, mini->sc.light[0].ratio);
	var.intersect = vec_add(mini->sc.cam[0].pos, vec_scale(ray_dir, t));
	var.to_light = vec_normalize(vec_substact(mini->sc.light[1].pos, var.intersect));
	var.to_cam = vec_normalize(vec_substact(mini->sc.cam[0].pos, var.intersect));
	var.halfway = vec_div(vec_normalize(vec_add(var.to_light, var.to_cam)), vec_get_norme(vec_add(var.to_light, var.to_cam)));
	dot = vec_dot(var.normal, vec_normalize(var.halfway));
	if (dot < 0)
		dot = 0;
	var.specular = color_scalar(light_color, pow(dot,180) * 1);
	var.specular.hit = true;
	// if (var.specular.r + var.specular.g + var.specular.b != 0)
	// 	var.specular = (t_color){0,0,255,1};
	return (var.specular);
}
