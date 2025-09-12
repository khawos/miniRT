/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:22:31 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/12 15:02:44 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	clash_of_clan(t_mini *mini, t_vec3 ray_direction, int x, int y)
{
	int			i;
	t_inter		k;

	i = 0;
	while (i < mini->N_OBJ)
	{
		k = intersect(mini, ray_direction, mini->sc.objet[i]);
		//if (k == out)
			//my_mlx_pixel_put(mini, x, y, 0xFFFFFF);
		if (k == in)
		{
			my_mlx_pixel_put(mini, x, y, color_shift(mini->sc.objet[i].color));		
		}	
		else if (k == edge)
			(void)k;
		//my_mlx_pixel_put(mini, x, y,(unsigned int)6579300);
		i++;
	}
}

t_vec3	get_left_corner_viewport(t_mini *mini)
{
	t_vec3	result;
	t_cam	cam;

	cam = mini->sc.cam[mini->cam_lock];
	result.x = cam.pos.x + cam.vec_dir.x + (
			cam.up.x * (cam.h / 2.0f)) - (cam.right.x * (cam.w / 2.0f));
	result.y = cam.pos.y + cam.vec_dir.y + (
			cam.up.y * (cam.h / 2.0f)) - (cam.right.y * (cam.w / 2.0f));
	result.z = cam.pos.z + cam.vec_dir.z + (
			cam.up.z * (cam.h / 2.0f)) - (cam.right.z * (cam.w / 2.0f));
	return (result);
}

t_boolean	cast(t_mini *mini)
{
	t_var_trace	var;
	t_vec3		ray_direction;
	t_cam		cam;

	cam = mini->sc.cam[mini->cam_lock];
	var.i = 0;
	var.delta_u = 0;
	while (var.i < HEIGHT)
	{
		var.j = 0;
		var.delta_v = 0;
		ray_direction = get_left_corner_viewport(mini);
		ray_direction = vec_substact(ray_direction,
				vec_scale(cam.up, var.delta_u));
		while (var.j < WIDTH)
		{
			clash_of_clan(mini, vec_normalize(vec_add(ray_direction,
						vec_scale(cam.right, var.delta_v))), var.j, var.i);
			var.j++;
			var.delta_v = var.delta_v + (cam.w / (double)WIDTH);
		}
		var.delta_u = var.delta_u + (cam.h / (double)HEIGHT);
		var.i++;
	}
	return (true);
}
