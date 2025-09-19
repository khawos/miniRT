/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:22:31 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/15 15:16:12 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color		put_background(int x, int y)
{
	t_color	color;
	(void)x;

	y = convert_range(y, HEIGHT, 0, 255);
	color = (t_color){y / 4, y / 5, y, 0};

	return (color);
}

void	put_pixel(t_mini *mini, t_vec3 ray_direction, int x, int y)
{
	t_color				color;

	color = intersect(mini, ray_direction);
	if (false == color.hit)
	{
		color = put_background(x, y);
		my_mlx_pixel_put(mini, x, y, color_shift(color));
	}
	else
		my_mlx_pixel_put(mini, x, y, color_shift(color));	
}

// t_vec3	get_left_corner_viewport(t_mini *mini)
// {
// 	t_vec3	result;
// 	t_cam	cam;

// 	cam = mini->sc.cam[mini->cam_lock];
// 	result.x = cam.pos.x + cam.vec_dir.x + (
// 			cam.up.x * (cam.h / 2.0f)) - (cam.right.x * (cam.w / 2.0f));
// 	result.y = cam.pos.y + cam.vec_dir.y + (
// 			cam.up.y * (cam.h / 2.0f)) - (cam.right.y * (cam.w / 2.0f));
// 	result.z = cam.pos.z + cam.vec_dir.z + (
// 			cam.up.z * (cam.h / 2.0f)) - (cam.right.z * (cam.w / 2.0f));
// 	return (result);
// }

t_vec3 get_left_corner_viewport(t_mini *mini)
{
    t_cam cam;
    t_vec3 result;

    cam = mini->sc.cam[mini->cam_lock];

    // Coin haut-gauche du viewport
    result = vec_add(cam.pos,
              vec_add(
                cam.vec_dir,
                vec_add(
                  vec_scale(cam.up, cam.h / 2.0f),
                  vec_scale(cam.right, -(cam.w / 2.0f))
                )
              ));
			  //printVec(cam.pos);

    return result;
}


t_boolean	cast(t_mini *mini)
{
	t_var_trace	var;
	t_vec3		ray_direction;
	t_cam		cam;

	cam = mini->sc.cam[mini->cam_lock];
	var.i = 0;
	var.delta_u = 0;
	printVec(get_left_corner_viewport(mini));
	while (var.i < HEIGHT)
	{
		var.j = 0;
		var.delta_v = 0;
		ray_direction = get_left_corner_viewport(mini);
		ray_direction = vec_substact(ray_direction,
				vec_scale(cam.up, var.delta_u));
		while (var.j < WIDTH)
		{
			put_pixel(mini, vec_normalize(vec_add(ray_direction,
						vec_scale(cam.right, var.delta_v))), var.j, var.i);
			var.j++;
			var.delta_v = var.delta_v + (cam.w / (double)WIDTH);
		}
		var.delta_u = var.delta_u + (cam.h / (double)HEIGHT);
		var.i++;
	}
	return (true);
}
