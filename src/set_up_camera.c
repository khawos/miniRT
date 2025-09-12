/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:13:29 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/12 13:41:08 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void    get_right_local_vector(t_mini *mini, int i)
{
	t_vec3  up_world;
	double	norme;
	
	up_world = (t_vec3){0, 0, 1};
	mini->sc.cam[i].right = vec_cross(up_world, mini->sc.cam[i].vec_dir);
	norme = vec_get_norme(vec_cross(up_world, mini->sc.cam[i].vec_dir));
	mini->sc.cam[i].right = vec_normalize(mini->sc.cam[i].right);
}

void    get_up_local_vector(t_mini *mini, int i)
{
	mini->sc.cam[i].up = vec_cross(mini->sc.cam[i].vec_dir, mini->sc.cam[i].right);
	//mini->sc.cam[i].up.x = vec_cross_x(mini->sc.cam[i].vec_dir, mini->sc.cam[i].right);
	//mini->sc.cam[i].up.y = vec_cross_y(mini->sc.cam[i].vec_dir, mini->sc.cam[i].right);
	//mini->sc.cam[i].up.z = vec_cross_z(mini->sc.cam[i].vec_dir, mini->sc.cam[i].right);
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
		mini->sc.cam[i].h = 2 * tanf(((double)mini->sc.cam[i].fov / 2.0f) * ((double)M_PI / 180.0f));
		mini->sc.cam[i].w = mini->sc.cam[i].h * ((double)WIDTH / (double)HEIGHT);
		printf("up = x : %f, y : %f, z : %f\n", mini->sc.cam[i].up.x , mini->sc.cam[i].up.y, mini->sc.cam[i].up.z);
		printf("right = x : %f, y : %f, z : %f\n", mini->sc.cam[i].right.x , mini->sc.cam[i].right.y, mini->sc.cam[i].right.z);
		printf("w : %f, h : %f\n", mini->sc.cam[i].w, mini->sc.cam[i].h);
		i++;
	}
}