/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:13:29 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/07 21:47:42 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void    get_right_local_vector(t_mini *mini, int i)
{
	t_vec3  up_world;
	double	norme;
	
	up_world = (t_vec3){0, 1, 0};
	mini->scene.cam[i].right.x = vec_cross_x(up_world, mini->scene.cam[i].vec_dir);
	mini->scene.cam[i].right.y = vec_cross_y(up_world, mini->scene.cam[i].vec_dir);
	mini->scene.cam[i].right.z = vec_cross_z(up_world, mini->scene.cam[i].vec_dir);
	norme = vec_normalize(vec_cross(up_world, mini->scene.cam[i].vec_dir));
	if (norme != 0)
	{
			mini->scene.cam[i].right.x /= norme;
			mini->scene.cam[i].right.y /= norme;
			mini->scene.cam[i].right.z /= norme;
	}
}

void    get_up_local_vector(t_mini *mini, int i)
{
	mini->scene.cam[i].up.x = vec_cross_x(mini->scene.cam[i].vec_dir, mini->scene.cam[i].right);
	mini->scene.cam[i].up.y = vec_cross_y(mini->scene.cam[i].vec_dir, mini->scene.cam[i].right);
	mini->scene.cam[i].up.z = vec_cross_z(mini->scene.cam[i].vec_dir, mini->scene.cam[i].right);
}

void	set_up_cam(t_mini *mini)
{
	int		i;

	i = 0;
	printAllCam(mini);
	while (i < mini->n_cam)
	{
		get_right_local_vector(mini, i) ;
		get_up_local_vector(mini, i);
		printf("up = x : %f, y : %f, z : %f\n", mini->scene.cam[i].up.x , mini->scene.cam[i].up.y, mini->scene.cam[i].up.z);
		printf("right = x : %f, y : %f, z : %f\n", mini->scene.cam[i].right.x , mini->scene.cam[i].right.y, mini->scene.cam[i].right.z);
		mini->scene.cam[i].h = 2 * tan((double)mini->scene.cam[i].fov / 2);
		mini->scene.cam[i].w = mini->scene.cam[i].h * ( WIDTH / HEIGHT);
		i++;
	}
}