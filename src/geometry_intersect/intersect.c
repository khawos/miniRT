/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:13:38 by amedenec          #+#    #+#             */
/*   Updated: 2025/10/29 18:57:08 by jbayonne         ###   ########.fr       */
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

t_boolean	is_intersect(t_mini *mini, t_vec3 ray_direction, t_vec3 origin, int index_light)
{
	t_is_intersect	var;

	var.i = -1;
	var.tmp = 0;
	var.intersect_to_light = vec_get_norme(vec_substact(mini->sc.light[index_light].pos,
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

static double	handle_object(t_mini *mini, t_ray ray, int i, double t)
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

double	get_nearest_triangle(int *closest, t_ray *ray, t_mini *mini)
{
	double	tmp;
	int		*tr_index;
	int		size;
	int		i;

	size = 0;
	tr_index = NULL;
	tr_index = search_tr_in_tree(mini->bvh, ray->origin, ray->current_dir, &size, tr_index);
	if (size == -1)
		return (ray->t_current = -1, ray->t_current);
	i = 0;
	if (tr_index)
	{
		while (i < size)
		{
			tmp = intersect_tr(ray->origin,
				ray->current_dir, mini->sc.objet_tr[tr_index[i]]);

			if (tmp > 0 && tmp < ray->t_current)
			{
				ray->t_current = tmp;
				*closest = tr_index[i];
			}
			i++;
		}
		free(tr_index);
	}
	return (ray->t_current);
}

t_color	intersect_loop(t_mini *mini, t_ray *ray)
{
	int		i;
	int		closest;
	double	tmp;

	closest = 0;
	i = -1;
	ray->t_current = RENDER_DISTANCE;
	while (++i < mini->N_OBJ)
	{
		tmp = handle_object(mini, *ray, i, ray->t_current);
		if (tmp < ray->t_current)
		{
			ray->t_current = tmp;
			closest = i;
		}
	}
	i = -1; 
	if (mini->bvh)
	{
		tmp = ray->t_current;
		ray->t_current = get_nearest_triangle(&closest, ray, mini);
		if (ray->t_current == -1)
		 	return ((t_color){0, 0, 0, 0});
		if (tmp > ray->t_current)
			return (light_ray(mini, ray, mini->sc.objet_tr[closest]));
		else
			ray->t_current = tmp;
	}
	if (ray->t_current != RENDER_DISTANCE)
		return (light_ray(mini, ray, mini->sc.objet[closest]));
	return ((t_color){0, 0, 0, 0});
}

t_color	mix_ray(t_color ray_color[SAMPLE_MAX])
{
	int	i;	
	int	r;	
	int	b;	
	int	g;
	
	i = 0;
	r = 0;
	b = 0;
	g = 0;
	while (i < SAMPLE_MAX)
	{
		r += ray_color[i].r;
		g += ray_color[i].g;
		b += ray_color[i].b;
		i++;
	}
	return ((t_color){(unsigned char)(r / SAMPLE_MAX), (unsigned char)(g / SAMPLE_MAX), (unsigned char)(b / SAMPLE_MAX)});
}

t_color	multiple_ray(t_mini *mini, t_ray *ray)
{
	t_color	ray_color[SAMPLE_MAX];
	int		i;

	i = 0;
	ray->current_dir = ray->dir_tab[0];
	if (mini->block_size != 1)
		return (intersect_loop(mini, ray));
	else
	{
		while (i < SAMPLE_MAX)
		{
			ray->current_dir = ray->dir_tab[i];
			ray_color[i] = intersect_loop(mini, ray);
			if (ray->t_current < ray->t_min)
				ray->t_min = ray->t_current;
			i++;
		}
		return (mix_ray(ray_color));
	}
}
