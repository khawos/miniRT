/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:22:31 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/29 18:04:05 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	put_background(int x, int y)
{
	t_color	color;

	(void)x;
	y = convert_range(y, HEIGHT, 0, 255);
	color = (t_color){y / 4, y / 5, y, 0};
	return (color);
}

t_color	apply_ambiant(t_mini *mini, t_color color)
{
	t_color	ambiant;

	ambiant = color_scalar(mini->sc.ambiant.color, mini->sc.ambiant.ratio);
	return (color_multiplie(ambiant, color));
}

void	put_pixel_block(t_mini *mini, t_vec3 *ray_direction, int x, int y)
{
	t_color			color;
	t_vec2			index;
	t_ray			ray;
	unsigned int	color_int;

	ray.origin = mini->sc.cam[mini->cam_lock].pos;
	ray.dir_tab = ray_direction;
	ray.bounce = 0;
	ray.t_min == RENDER_DISTANCE;
	color = multiple_ray(mini, &ray);
	if (ray.t_min == -1)
		return ;									// error kill ici
	if (ray.t_current == RENDER_DISTANCE)
	{
		color = put_background(x, y);
	}
	color_int = color_shift(color);
	if (x + mini->block_size - 1 >= WIDTH || y + mini->block_size - 1 >= HEIGHT)
		return ;
	index.u = 0;
	while (index.u < mini->block_size)
	{
		index.v = -1;
		while (++index.v < mini->block_size)
			my_mlx_pixel_put(mini, x + index.v, y + index.u, color_int);
		index.u++;
	}
}

static void	render_line(t_mini *mini, t_var_trace *var, double step_u, t_vec3 ray_d)
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
			return ;	// error kill here
		ray_dir = ray_offset(ray_dir, bounds, mini);
		put_pixel_block(mini, ray_dir, var->j, var->i);
		var->j += mini->block_size;
		bounds.delta_v_min += mini->block_size * step_v;
		free(ray_dir);
	}
}

void	*cast(void *arg)
{
	t_var_trace	var;
	t_vec3		ray_direction;
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
		ray_direction = vec_substact(mini->left_corner,
				vec_scale(cam.up, var.delta_u));
		sem_wait(mini->s_img);
		render_line(mini, &var, step_u, ray_direction);
		var.i += mini->block_size;
		var.delta_u += mini->block_size * step_u;
		sem_post(mini->s_img);
	}
	return (NULL);
}
