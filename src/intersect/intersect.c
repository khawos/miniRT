/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:13:38 by amedenec          #+#    #+#             */
/*   Updated: 2025/11/02 13:19:48 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	else if (tr == var.objet.type)
	{
		var.tmp = intersect_tr(origin, ray_dir, var.objet);
		if (var.tmp > 0.0000000001)
			if (var.tmp < var.intersect_to_light)
				return (true);
	}
	return (false);
}

t_boolean	is_intersect_bis2(t_vec3 ray_dir, t_vec3 origin, t_is_intersect var)
{
	if (pl == var.objet.type)
	{
		var.tmp = intersect_pl(origin, ray_dir, var.objet);
		if (var.tmp > 0.1)
		{
			if (var.tmp < var.intersect_to_light)
				return (true);
		}
	}	
	return (false);
}

t_boolean	is_intersect(t_mini *mini, t_vec3 ray_direction, t_vec3 origin,
	int index_light)
{
	t_is_intersect	var;

	var.i = -1;
	var.tmp = 0;
	var.intersect_to_light = vec_get_norme(vec_substact
			(mini->sc.light[index_light].pos,
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
		if (is_intersect_bis(ray_direction, origin, var)
			&& is_intersect_bis2(ray_direction, origin, var))
			return (true);
	}
	return (false);
}

double	handle_object(t_mini *mini, t_ray ray, int i, double t)
{
	double	tmp;
	t_objet	obj;

	obj = mini->sc.objet[i];
	tmp = 0;
	if (obj.type == sp)
		tmp = intersect_sp(ray.origin, ray.current_dir, obj);
	else if (obj.type == pl)
		tmp = intersect_pl(ray.origin, ray.current_dir, obj);
	else if (obj.type == cy)
	{
		obj.vec_dir = vec_normalize(obj.vec_dir);
		tmp = intersect_cy(ray.origin, ray.current_dir, obj);
		if (tmp > 0 && tmp < t)
			return (tmp);
		tmp = intersect_cap(ray.origin, ray.current_dir, obj);
		if (tmp > 0 && tmp < t)
			return (tmp);
	}
	if (tmp > 0 && tmp < t)
		return (tmp);
	return (t);
}
