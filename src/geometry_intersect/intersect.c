/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:13:38 by amedenec          #+#    #+#             */
/*   Updated: 2025/10/06 12:15:27 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

typedef struct s_is_intersect
{
	double		tmp;
	int			i;
	double		intersect_to_light;
	t_objet		objet;
}				t_is_intersect;

t_boolean	is_intersect_bis(t_vec3 ray_dir, t_vec3 origin, t_is_intersect var)
{
	if (cy == var.objet.type)
	{
		var.objet.vec_dir = vec_normalize(var.objet.vec_dir);
		var.tmp = intersect_cy(origin, ray_dir, var.objet);
		if (var.tmp > -0.0000000001)
			if (var.tmp < var.intersect_to_light)
				return (true);
		var.tmp = intersect_cap(origin, ray_dir, var.objet);
		if (var.tmp > 0.0000000001)
			if (var.tmp < var.intersect_to_light)
				return (true);
	}
	return (false);
}

t_boolean	is_intersect(t_mini *mini, t_vec3 ray_direction, t_vec3 origin)
{
	t_is_intersect	var;

	var.i = -1;
	var.tmp = 0;
	var.intersect_to_light = vec_get_norme(vec_substact(mini->sc.light[1].pos,
				origin));
	while (++var.i < mini->N_OBJ)
	{
		var.objet = mini->sc.objet[var.i];
		if (sp == var.objet.type)
		{
			var.tmp = intersect_sp(origin, ray_direction, var.objet);
			if (var.tmp > -0.0000000001)
				if (var.tmp < var.intersect_to_light)
					return (true);
		}
		if (is_intersect_bis(ray_direction, origin, var))
			return (true);
	}
	return (false);
}

static double	handle_object(t_mini *mini, t_vec3 ray_dir, int i, double t)
{
	double	tmp;
	t_objet	obj;

	obj = mini->sc.objet[i];
	tmp = 0;
	if (obj.type == sp)
		tmp = intersect_sp(mini->sc.cam[mini->cam_lock].pos, ray_dir, obj);
	else if (obj.type == pl)
		tmp = intersect_pl(mini->sc.cam[mini->cam_lock].pos, ray_dir, obj);
	else if (obj.type == cy)
	{
		obj.vec_dir = vec_normalize(obj.vec_dir);
		tmp = intersect_cy(mini->sc.cam[mini->cam_lock].pos, ray_dir, obj);
		if (tmp > 0 && tmp < t)
			return (tmp);
		tmp = intersect_cap(mini->sc.cam[mini->cam_lock].pos, ray_dir, obj);
		if (tmp > 0 && tmp < t)
			return (tmp);
	}
	if (tmp > 0 && tmp < t)
		return (tmp);
	return (t);
}

t_color	intersect_loop(t_mini *mini, t_vec3 ray_dir, double *t)
{
	int		i;
	int		closest;
	double	tmp;

	*t = RENDER_DISTANCE;
	closest = 0;
	i = -1;
	while (++i < mini->N_OBJ)
	{
		tmp = handle_object(mini, ray_dir, i, *t);
		if (tmp < *t)
		{
			*t = tmp;
			closest = i;
		}
	}
	if (*t != RENDER_DISTANCE)
		return (light_ray(mini, ray_dir, *t, mini->sc.objet[closest]));
	return ((t_color){0, 0, 0, 0});
}
