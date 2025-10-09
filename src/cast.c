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

#include "miniRT.h"

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

// AKA clash_of_clan
void	put_pixel(t_mini *mini, t_vec3 ray_direction, int x, int y)
{
	t_color				color;
	double				t;

	color = intersect(mini, ray_direction, &t);
	if (t == RENDER_DISTANCE)
	{
		color = put_background(x, y);
		my_mlx_pixel_put(mini, x, y, color_shift(color));
		return ;
	} 
	my_mlx_pixel_put(mini, x, y, color_shift(color));
}
//GPT
// void	put_pixel_block(t_mini *mini, t_vec3 ray_direction, int x, int y)
// {
// 	t_color	color;
// 	double	t;
// 	unsigned int color_int;

// 	color = intersect(mini, ray_direction, &t);
// 	if (t == RENDER_DISTANCE)
// 	{
// 		color = put_background(x, y);
// 		my_mlx_pixel_put(mini, x, y, color_shift(color));
// 		my_mlx_pixel_put(mini, x + 1 , y, color_shift(color));
// 		my_mlx_pixel_put(mini, x, y + 1, color_shift(color));
// 		my_mlx_pixel_put(mini, x + 1, y + 1, color_shift(color));
		
// 		return ;
// 	} 
// 	color_int = color_shift(color);

// 	if (x + 1 >= WIDTH || y + 1 >= HEIGHT)
// 		return ;

// 	my_mlx_pixel_put(mini, x, y, color_int);
// 	my_mlx_pixel_put(mini, x + 1, y, color_int);
// 	my_mlx_pixel_put(mini, x, y + 1, color_int);
// 	my_mlx_pixel_put(mini, x + 1, y + 1, color_int);
// }

void	put_pixel_block(t_mini *mini, t_vec3 ray_direction, int x, int y)
{
	t_color	color;
	double	t;
	int		i, j;
	unsigned int color_int;


	color = intersect(mini, ray_direction, &t);
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



t_vec3	get_left_corner_viewport(t_mini mini)
{
	t_vec3	result;
	t_cam	cam;

	cam = mini.sc.cam[mini.cam_lock];
	result.x = cam.pos.x + cam.vec_dir.x + (
			cam.up.x * (cam.h / 2.0f)) - (cam.right.x * (cam.w / 2.0f));
	result.y = cam.pos.y + cam.vec_dir.y + (
			cam.up.y * (cam.h / 2.0f)) - (cam.right.y * (cam.w / 2.0f));
	result.z = cam.pos.z + cam.vec_dir.z + (
			cam.up.z * (cam.h / 2.0f)) - (cam.right.z * (cam.w / 2.0f));
	return (result);
}

double	get_delta_u(t_cam cam, int min)
{
	double	delta_u;
	int		i;

	i = 0;
	delta_u = 0;
	while (i != min && min != -1)
	{
		delta_u = delta_u + (cam.h / (double)HEIGHT);
		i++;
	}
	return (delta_u);
}

static void	render_line(t_mini *mini, t_var_trace *var, t_cam cam, t_vec3 ray_direction)
{
	t_vec3	ray_dir;

	var->j = 0;
	var->delta_v = 0;
	while (var->j < WIDTH)
	{
		ray_dir = vec_normalize(vec_substact(
					vec_add(ray_direction, vec_scale(cam.right, var->delta_v)),
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
		pthread_mutex_lock(&mini->render_mutex);
		ray_direction = vec_substact(mini->left_corner,
				vec_scale(cam.up, var.delta_u));
		render_line(mini, &var, cam, ray_direction);
		var.i += mini->block_size;
		var.delta_u += mini->block_size * (cam.h / (double)HEIGHT);
		pthread_mutex_unlock(&mini->render_mutex);
	}
	return (NULL);
}
