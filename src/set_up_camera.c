/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:13:29 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/15 14:59:09 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	vec_abs(t_vec3 i)
{
	t_vec3 result;

	result.x = fabs(i.x); 
	result.y = fabs(i.y); 
	result.z = fabs(i.z); 
	return (result);
}

void	get_right_local_vector(t_mini *mini, int i)
{
	t_vec3	up_world;

	up_world = (t_vec3){0, 0, 1};
	if (vec_dot(up_world, mini->sc.cam[i].vec_dir) == 1)
		up_world = (t_vec3){0, 1, 0};
	mini->sc.cam[i].right = vec_cross(mini->sc.cam[i].vec_dir, up_world);
	mini->sc.cam[i].right = vec_abs(vec_normalize(mini->sc.cam[i].right));
}

void	get_up_local_vector(t_mini *mini, int i)
{
	mini->sc.cam[i].up = vec_abs(vec_cross(
			mini->sc.cam[i].vec_dir, mini->sc.cam[i].right));
}

void	set_up_cam(t_mini *mini)
{
	int		i;

	i = 0;
	while (i < mini->n_cam)
	{
		get_right_local_vector(mini, i);
		get_up_local_vector(mini, i);
		mini->sc.cam[i].h = 2 * tan
			(((double)mini->sc.cam[i].fov / 2.0f) * ((double)M_PI / 180.0f));
		mini->sc.cam[i].w = mini->sc.cam[i].h * (
				(double)WIDTH / (double)HEIGHT);
		mini->sc.cam[i].up = vec_normalize(mini->sc.cam[i].up);
		mini->sc.cam[i].right = vec_normalize(mini->sc.cam[i].right);
		i++;
	}
}
