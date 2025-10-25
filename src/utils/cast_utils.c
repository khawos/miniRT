/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-09 17:17:24 by jbayonne          #+#    #+#             */
/*   Updated: 2025-10-09 17:17:24 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
