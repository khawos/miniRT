/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:22:31 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/09 15:03:05 by amedenec         ###   ########.fr       */
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

void	put_pixel_block(t_mini *mini, t_vec3 ray_direction, int x, int y)
{
	t_color			color;
	double			t;
	int				i;
	int				j;
	unsigned int	color_int;

	color = intersect_loop(mini, ray_direction, &t);
	if (t == -1)
		return ;									// error kill ici
	if (t == RENDER_DISTANCE)
		color = put_background(x, y);
	color_int = color_shift(color);
	if (x + mini->block_size - 1 >= WIDTH || y + mini->block_size - 1 >= HEIGHT)
		return ;
	i = 0;
	while (i < mini->block_size)
	{
		j = -1;
		while (++j < mini->block_size)
			my_mlx_pixel_put(mini, x + j, y + i, color_int);
		i++;
	}
}

static void	render_line(t_mini *mini, t_var_trace *var, t_cam cam, t_vec3 ray_d)
{
	t_vec3	ray_dir;

	var->j = 0;
	var->delta_v = 0;
	while (var->j < WIDTH)
	{
		ray_dir = vec_normalize(vec_substact(
					vec_add(ray_d, vec_scale(cam.right, var->delta_v)),
					cam.pos));
		put_pixel_block(mini, ray_dir, var->j, var->i);
		var->j += mini->block_size;
		var->delta_v += mini->block_size * (cam.w / (double)WIDTH);
	}
}

void	*cast(void *arg)
{
	t_var_trace	var;
	t_vec3		ray_direction;
	t_cam		cam;
	t_mini		*mini;

	mini = (t_mini *)arg;
	cam = mini->sc.cam[mini->cam_lock];
	var.i = mini->min;
	var.max = mini->max;
	var.delta_u = get_delta_u(cam, var.i);
	var.block_size = mini->block_size;
	sem_post(mini->m_cast);
	while (var.i <= var.max)
	{
		ray_direction = vec_substact(mini->left_corner,
				vec_scale(cam.up, var.delta_u));
		sem_wait(mini->s_img);
		render_line(mini, &var, cam, ray_direction);
		var.i += mini->block_size;
		var.delta_u += mini->block_size * (cam.h / (double)HEIGHT);
		sem_post(mini->s_img);
	}
	return (NULL);
}
