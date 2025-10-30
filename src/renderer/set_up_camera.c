/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:13:29 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/29 00:45:53 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_vec3	vec_abs(t_vec3 i)
// {
// 	t_vec3	result;

// 	result.x = fabs(i.x);
// 	result.y = fabs(i.y);
// 	result.z = fabs(i.z);
// 	return (result);
// }

t_vec3	vec_safe_normalize(t_vec3 v) // julien j'ai change parce que l'ancien desaxe right up et front, (plus hortogonaux)
{
	double	len;

	len = vec_get_norme(v);
	return (vec_scale(v, 1.0 / len));
}


// void	get_right_local_vector(t_mini *mini, int i)
// {
// 	t_vec3	up_world;

// 	up_world = (t_vec3){0, 0, 1};
// 	if (vec_dot(up_world, mini->sc.cam[i].vec_dir) == 1)
// 		up_world = (t_vec3){0, 1, 0};
// 	mini->up_world = up_world;
// 	mini->sc.cam[i].right = vec_cross(mini->sc.cam[i].vec_dir, up_world);
// 	mini->sc.cam[i].right = vec_abs(vec_normalize(mini->sc.cam[i].right));
// }

void	get_right_local_vector(t_mini *mini, int i)
{
	t_vec3	up_world;
	t_vec3	dir;
	t_vec3	right;

	up_world = (t_vec3){0.0, 0.0, 1.0};
	dir = mini->sc.cam[i].vec_dir;


	mini->up_world = up_world;

	right = vec_cross(dir, up_world);
	right = vec_safe_normalize(right);    //normalise, sans prendre les absolus comme des golmon

	mini->sc.cam[i].right = right;
}

// void	get_up_local_vector(t_mini *mini, int i)
// {
// 	mini->sc.cam[i].up = vec_abs(vec_cross(
// 				mini->sc.cam[i].vec_dir, mini->sc.cam[i].right));
// }

void	get_up_local_vector(t_mini *mini, int i)
{
	t_vec3	up;

	// up = cross(right, vec_dir) garantit la cohérence du repère 
	up = vec_cross(mini->sc.cam[i].right, mini->sc.cam[i].vec_dir);
	mini->sc.cam[i].up = vec_safe_normalize(up);
}

// void	set_up_cam(t_mini *mini)
// {
// 	int		i;

// 	i = 0;
// 	while (i < mini->n_cam)
// 	{
// 		get_right_local_vector(mini, i);
// 		get_up_local_vector(mini, i);
// 		mini->sc.cam[i].h = 2 * tan
// 			(((double)mini->sc.cam[i].fov / 2.0f) * ((double)M_PI / 180.0f));
// 		mini->sc.cam[i].w = mini->sc.cam[i].h * (
// 				(double)WIDTH / (double)HEIGHT);
// 		mini->sc.cam[i].up = vec_normalize(mini->sc.cam[i].up);
// 		mini->sc.cam[i].right = vec_normalize(mini->sc.cam[i].right);
// 		mini->sc.cam[i].yaw = 0;
// 		mini->sc.cam[i].pitch = 0;
// 		i++;
// 	}
// }

void	set_up_cam(t_mini *mini)
{
	int		i;

	i = 0;
	while (i < mini->n_cam)
	{
		get_right_local_vector(mini, i);
		get_up_local_vector(mini, i);
		mini->sc.cam[i].h = 2 * tan(((double)mini->sc.cam[i].fov / 2.0) * (M_PI / 180.0));
		mini->sc.cam[i].w = mini->sc.cam[i].h * ((double)WIDTH / (double)HEIGHT);
		/* normalisation déjà faite par vec_safe_normalize */
		/* NE PAS reset yaw/pitch ici si tu veux garder les rotations actuelles */
		i++;
	}
}
