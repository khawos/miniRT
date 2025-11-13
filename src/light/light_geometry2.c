/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_geometry2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:18:07 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/06 14:18:10 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_light_ctx
{
	t_mini			*mini;
	t_objet			obj;
	t_ray			*ray;
	double			dot;
	t_light_utils	utils;
}	t_light_ctx;

void	light_cy_util(double *dot, t_vec3 *normal, t_objet obj, t_vec3 to_light)
{
	*normal = obj.vec_dir;
	*dot = fabs(vec_dot(*normal, vec_normalize(to_light)));
}	

t_boolean	is_inside_cylinder(t_vec3 point, t_objet obj)
{
	double	h;
	t_vec3	base;
	t_vec3	to_point;
	t_vec3	proj;

	base = vec_substact(obj.pos, vec_scale(obj.vec_dir, obj.height / 2));
	to_point = vec_substact(point, base);
	h = vec_dot(to_point, obj.vec_dir);
	if (h < 0 || h > obj.height)
		return (false);
	proj = vec_add(base, vec_scale(obj.vec_dir, h));
	return (vec_get_norme(vec_substact(point, proj)) < obj.diameter / 2);
}

double	cyl_light_dot(t_light_ctx *ctx, t_vec3 to_light, t_vec3 normal)
{
	t_vec3	light_pos;
	t_vec3	ray_origin;

	light_pos = ctx->mini->sc.light[ctx->utils.i].pos;
	ray_origin = ctx->ray->origin;
	if (is_inside_cylinder(light_pos, ctx->obj)
		&& is_inside_cylinder(ray_origin, ctx->obj))
		return (1.0);
	return (vec_dot(normal, vec_normalize(to_light)));
}

t_vec3	cyl_normal(t_objet obj, t_vec3 p)
{
	t_vec3	base;

	base = vec_substact(obj.pos, vec_scale(obj.vec_dir, obj.height / 2));
	return (vec_normalize(vec_substact(p,
				vec_add(base, vec_scale(obj.vec_dir,
						vec_dot(vec_substact(p, base), obj.vec_dir))))));
}

t_color	light_cy(t_mini *mini, t_objet obj, t_ray *ray, t_light_utils utils)
{
	t_light_ctx	ctx;
	t_vec3		p;
	t_vec3		to_light;
	t_vec3		normal;

	ctx.mini = mini;
	ctx.obj = obj;
	ctx.ray = ray;
	ctx.utils = utils;
	if (shadow_ray(mini, *ray, ray->t, utils.i))
		return ((t_color){0, 0, 0});
	p = vec_add(ray->origin, vec_scale(ray->current_dir, ray->t));
	to_light = vec_substact(mini->sc.light[utils.i].pos, p);
	if (ray->t == intersect_cap(ray->origin, ray->current_dir, obj))
		light_cy_util(&ctx.dot, &normal, obj, to_light);
	else
	{
		normal = cyl_normal(obj, p);
		ctx.dot = cyl_light_dot(&ctx, to_light, normal);
	}
	if (ctx.dot < 0)
		ctx.dot = 0;
	return (color_scalar(color_multiplie(obj.color,
				color_scalar(mini->sc.light[utils.i].color,
					mini->sc.light[utils.i].ratio)), ctx.dot));
}
