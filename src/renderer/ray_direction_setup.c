/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_direction_setup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:23:00 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/30 21:29:22 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	randfrom(double min, double max)
{
	double result;
	
	result = convert_range(rand(), RAND_MAX, min, max);
	return (result);
}

t_vec3	create_first_ray_dir(t_mini *mini, t_delta_offset bounds)
{
	double	delta_u;
	double	delta_v;
	t_vec3	ray_dir;
	t_vec3	u_axe;
	t_cam	cam;

	delta_u = randfrom(bounds.delta_u_min, bounds.delta_u_max);
	delta_v = randfrom(bounds.delta_v_min, bounds.delta_v_max);
	cam = mini->sc.cam[mini->cam_lock];
	u_axe = vec_substact(mini->left_corner, vec_scale(cam.up, delta_u));
	ray_dir = vec_normalize(vec_substact(
		vec_add(u_axe, vec_scale(cam.right, delta_v)),
		cam.pos));
	return (ray_dir);
}

t_vec3	*ray_direction_allocation(void)
{
	t_vec3	*ray_dir;

	ray_dir = malloc(sizeof(t_vec3) * (SAMPLE_MAX + 1));
	if (!ray_dir)
		return (NULL);
	return (ray_dir);
}

t_vec3	*ray_offset(t_vec3	*ray_direction, t_delta_offset bounds, t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->block_size != 1)
	{
		ray_direction[i] = create_first_ray_dir(mini, bounds);
		return (ray_direction);
	}
	while (i < SAMPLE_MAX)
	{
		ray_direction[i] = create_first_ray_dir(mini, bounds);
		i++;
	}
	return (ray_direction);
}