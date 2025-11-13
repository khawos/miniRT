/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:22:31 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/12 15:04:05 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	put_background(int x, int y)
{
	t_color	color;

	(void)x;
	y = convert_range(y, HEIGHT, 0, 255);
	color = (t_color){y / 4, y / 5, y};
	return (color);
}

t_color	apply_ambiant(t_mini *mini, t_color color)
{
	t_color	ambiant;

	(void)color;
	ambiant = color_scalar(mini->sc.ambiant.color, mini->sc.ambiant.ratio);
	return (ambiant);
}

t_boolean	put_pixel_block(t_mini *mini, t_vec3 *ray_direction
	, t_var_trace var)
{
	t_color			color;
	t_vec2			index;
	t_ray			ray;
	unsigned int	color_int;

	ray.origin = mini->sc.cam[mini->cam_lock].pos;
	ray.dir_tab = ray_direction;
	ray.bounce = 0;
	color = multiple_ray(mini, &ray);
	if (ray.t == -1)
		return (false);
	if (ray.t == RENDER_DISTANCE)
		color = put_background(var.j, var.i);
	color_int = color_shift(color);
	index.u = 0;
	while (index.u < mini->block_size)
	{
		index.v = -1;
		while (++index.v < mini->block_size)
			my_mlx_pixel_put(mini, var, index, color_int);
		index.u++;
	}
	return (true);
}

static t_boolean	render_line(t_mini *mini, t_var_trace *var, double step_u)
{
	t_vec3						*ray_dir;
	t_delta_offset				bounds;
	double						step_v;
	t_cam						cam;

	cam = mini->sc.cam[mini->cam_lock];
	bounds.delta_u_min = var->delta_u;
	bounds.delta_u_max = var->delta_u + (step_u * 1);
	var->j = 0;
	bounds.delta_v_min = 0;
	step_v = (cam.w / (double)WIDTH);
	while (var->j < WIDTH)
	{
		bounds.delta_v_max = bounds.delta_v_min + (step_v * 1);
		ray_dir = ray_direction_allocation();
		if (!ray_dir)
			return (false);
		ray_dir = ray_offset(ray_dir, bounds, mini);
		if (!put_pixel_block(mini, ray_dir, *var))
			return (free(ray_dir), false);
		var->j += mini->block_size;
		bounds.delta_v_min += mini->block_size * step_v;
		free(ray_dir);
	}
	return (true);
}

void	*cast(void *arg)
{
	t_var_trace	var;
	t_cam		cam;
	t_mini		*mini;
	double		step_u;

	mini = (t_mini *)arg;
	cam = mini->sc.cam[mini->cam_lock];
	var.i = mini->min;
	var.max = mini->max;
	var.delta_u = get_delta_u(cam, var.i);
	var.block_size = mini->block_size;
	step_u = (cam.h / (double)HEIGHT);
	sem_post(mini->m_cast);
	while (var.i <= var.max)
	{
		sem_wait(mini->s_img);
		if (!render_line(mini, &var, step_u))
			return (error_in_thread(mini), NULL);
		var.i += mini->block_size;
		var.delta_u += mini->block_size * step_u;
		sem_post(mini->s_img);
	}
	return (NULL);
}
