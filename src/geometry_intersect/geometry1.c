/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:40:56 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/12 16:14:42 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_cy_ctx
{
	t_vec3		origin;
	t_vec3		ray_d;
	t_objet		*obj;
	t_equation	*var;
}	t_cy_ctx;

void	init_var_cy(t_vec3 origin, t_vec3 ray_d, t_objet *obj, t_equation *var)
{
	t_vec3	hb;
	t_vec3	vec_dir_scale;
	double	dot_ray_chap;
	double	dot_w_chap;

	vec_dir_scale = vec_scale(obj->vec_dir, obj->height / 2);
	var->base = vec_substact(obj->pos, vec_dir_scale);
	var->h = vec_add(obj->pos, vec_dir_scale);
	var->wase = vec_substact(origin, var->base);
	hb = vec_normalize(vec_substact(var->h, var->base));
	dot_w_chap = vec_dot(var->wase, hb);
	dot_ray_chap = vec_dot(ray_d, hb);
	var->a = vec_dot(ray_d, ray_d) - pow(dot_ray_chap, 2);
	var->b = 2 * (vec_dot(ray_d, var->wase) - dot_ray_chap * dot_w_chap);
	var->c = vec_dot(var->wase, var->wase) - pow(dot_w_chap, 2)
		- pow(obj->diameter / 2, 2);
	var->delta = pow(var->b, 2) - 4 * var->a * var->c;
}

static double	get_valid_inter(t_cy_ctx *ctx, double s)
{
	double	dot;

	ctx->var->intersect = vec_add(ctx->origin, vec_scale(ctx->ray_d, s));
	ctx->var->intersect = vec_substact(ctx->var->intersect, ctx->var->base);
	dot = vec_dot(ctx->var->intersect, ctx->obj->vec_dir);
	if (dot < 0 || dot > ctx->obj->height)
		return (-1);
	return (s);
}

double	inter_cy_2(t_vec3 origin, t_vec3 ray_d, t_objet *obj, t_equation *var)
{
	t_cy_ctx	ctx;

	ctx.origin = origin;
	ctx.ray_d = ray_d;
	ctx.obj = obj;
	ctx.var = var;
	if (var->s1 > var->s2 && var->s2 < 0)
		return (get_valid_inter(&ctx, var->s1));
	if (var->s1 < var->s2 && var->s1 < 0)
		return (get_valid_inter(&ctx, var->s2));
	if (var->s1 > var->s2)
		return (get_valid_inter(&ctx, var->s2));
	if (var->s1 < var->s2)
		return (get_valid_inter(&ctx, var->s1));
	return (0);
}

double	intersect_cy(t_vec3 origin, t_vec3 ray_direction, t_objet object)
{
	t_equation	var;

	init_var_cy(origin, ray_direction, &object, &var);
	if (var.delta > 0)
	{
		var.s1 = (-var.b + sqrt(var.delta)) / (2 * var.a);
		var.s2 = (-var.b - sqrt(var.delta)) / (2 * var.a);
		if ((var.s1 < 0 && var.s2 < 0))
			return (-1);
		return (inter_cy_2(origin, ray_direction, &object, &var));
	}
	if (0 == var.delta)
		return (-var.b / (2 * var.a));
	return (-1);
}
