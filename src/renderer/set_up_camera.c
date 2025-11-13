/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:13:29 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/02 13:16:54 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec_safe_normalize(t_vec3 v)
{
	double	len;

	len = vec_get_norme(v);
	return (vec_scale(v, 1.0 / len));
}

void	get_right_local_vector(t_mini *mini, int i)
{
	t_vec3	up_world;
	t_vec3	dir;
	t_vec3	right;

	up_world = (t_vec3){0, 0, 1};
	dir = mini->sc.cam[i].vec_dir;
	if (vec_dot(up_world, mini->sc.cam[i].vec_dir) == 1)
		up_world = (t_vec3){0, 1, 0};
	mini->up_world = up_world;
	right = vec_cross(dir, up_world);
	right = vec_safe_normalize(right);
	mini->sc.cam[i].right = right;
}

void	get_up_local_vector(t_mini *mini, int i)
{
	t_vec3	up;

	up = vec_cross(mini->sc.cam[i].right, mini->sc.cam[i].vec_dir);
	mini->sc.cam[i].up = vec_safe_normalize(up);
}

void	set_up_cam(t_mini *mini)
{
	int		i;

	i = 0;
	while (i < mini->n_cam)
	{
		get_right_local_vector(mini, i);
		get_up_local_vector(mini, i);
		mini->sc.cam[i].h = 2 * tan(((double)mini->sc.cam[i].fov / 2.0)
				* (M_PI / 180.0));
		mini->sc.cam[i].w = mini->sc.cam[i].h
			* ((double)WIDTH / (double)HEIGHT);
		i++;
	}
}
