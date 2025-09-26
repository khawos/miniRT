/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:13:38 by amedenec          #+#    #+#             */
/*   Updated: 2025/09/26 13:09:00 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_boolean	is_intersect(t_mini *mini, t_vec3 ray_direction, t_vec3 origin)
{
	double		tmp;
	int			i;

	i = -1;
	tmp = 0;
	while (++i < mini->N_OBJ)
	{
		mini->sc.objet[i].color.hit = false;
		if (sp == mini->sc.objet[i].type)
		{
			tmp = intersect_sp(origin, ray_direction, &mini->sc.objet[i]);
			if (tmp > -0.0000000001)
				return (true);
		}
		if (cy == mini->sc.objet[i].type)
		{
			tmp = intersect_cy(origin, ray_direction, &mini->sc.objet[i]);
			if (tmp > -0.0000000001)
				return (true);
			tmp = intersect_cap(origin, ray_direction, &mini->sc.objet[i]);
			if (tmp > 0.0000000001)
				return (true);
		}
	}
	return (false);
}

static double	handle_object(t_mini *mini, t_vec3 ray_dir, int i, double t)
{
	double	tmp;
	t_objet	*obj;

	obj = &mini->sc.objet[i];
	tmp = 0;
	if (obj->type == sp)
		tmp = intersect_sp(mini->sc.cam[mini->cam_lock].pos, ray_dir, obj);
	else if (obj->type == pl)
		tmp = intersect_pl(mini->sc.cam[mini->cam_lock].pos, ray_dir, obj);
	else if (obj->type == cy)
	{
		tmp = intersect_cy(mini->sc.cam[mini->cam_lock].pos, ray_dir, obj);
		if (tmp > 0 && tmp < t)
			return (obj->cap = false, tmp);
		tmp = intersect_cap(mini->sc.cam[mini->cam_lock].pos, ray_dir, obj);
		if (tmp > 0 && tmp < t)
			return (obj->cap = true, tmp);
	}
	if (tmp > 0 && tmp < t)
		return (tmp);
	return (t);
}

t_color	intersect(t_mini *mini, t_vec3 ray_dir)
{
	int		i;
	int		closest;
	double	t;
	double	tmp;

	t = 10000;
	closest = 0;
	i = -1;
	while (++i < mini->N_OBJ)
	{
		mini->sc.objet[i].color.hit = false;
		mini->sc.objet[i].cap = true;
		tmp = handle_object(mini, ray_dir, i, t);
		if (tmp < t)
		{
			t = tmp;
			closest = i;
		}
	}
	if (mini->sc.objet[closest].color.hit)
		return (light_ray(mini, ray_dir, t, mini->sc.objet[closest]));
	return (mini->sc.objet[closest].color);
}
