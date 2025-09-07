/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-06 14:22:31 by jbayonne          #+#    #+#             */
/*   Updated: 2025-09-06 14:22:31 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief 
 * 
 * get_pixel_in_space permets de connaitre l'emplacement 3D d'un pixel de notre plan projete.
 * 
 * @param P   : point dans l'espace 3D d'un pixel projete sur le plan de taille w * h 
 * @param d_u : d_u correspond a delta_u, parametre de variaton du vecteur U (up). 
 * @param d_v : d_u correspond a delta_u, parametre de variaton du vecteur R (right). 
 * @param mini: mini tu connais y a tout e qui faut dedans
 *
 */ 
void	get_pixel_in_space(t_vec3 *P, double d_u, double d_v, t_mini *mini)
{
	P->x = mini->scene.cam[mini->cam_lock].pos.x + 
		mini->scene.cam[mini->cam_lock].vec_dir.x + 
			(mini->scene.cam[mini->cam_lock].right.x * d_u) + 
				(mini->scene.cam[mini->cam_lock].up.x * d_v);
	P->y = mini->scene.cam[mini->cam_lock].pos.y + 
		mini->scene.cam[mini->cam_lock].vec_dir.y + 
			(mini->scene.cam[mini->cam_lock].right.y * d_u) + 
				(mini->scene.cam[mini->cam_lock].up.y * d_v);
	P->z = mini->scene.cam[mini->cam_lock].pos.z + 
		mini->scene.cam[mini->cam_lock].vec_dir.z + 
			(mini->scene.cam[mini->cam_lock].right.z * d_u) + 
				(mini->scene.cam[mini->cam_lock].up.z * d_v);
}

/**
 * @brief get ray direction
 * 
 * Donne a ray_D un vecteur norme dans la direction de la cam vers P
 * 
 * @param ray_d directon du ray cast par la cam
 * @param P point dans l'espace 3D d'un pixel projete sur le plan de taille w * h 
 * @param mini mini tu connais y a tout e qui faut dedans
 * 
 */
void	get_ray_direction(t_vec3 *ray_D, t_vec3 *P, t_mini *mini)
{
	double	norme_ray_D;

	ray_D->x = P->x - mini->scene.cam[mini->cam_lock].pos.x;
	ray_D->y = P->y - mini->scene.cam[mini->cam_lock].pos.y;
	ray_D->z = P->z - mini->scene.cam[mini->cam_lock].pos.z;
	norme_ray_D = vec_normalize(*ray_D);
	ray_D->x = ray_D->x / norme_ray_D;
	ray_D->y = ray_D->y / norme_ray_D;
	ray_D->z = ray_D->z / norme_ray_D;
}

void	get_ray(t_mini *mini, double d_u, double d_v, t_vec3 *ray_dir)
{
	t_vec3		pixel_on_project_plan;

	get_pixel_in_space(&pixel_on_project_plan, d_u, d_v, mini);
	get_ray_direction(ray_dir, &pixel_on_project_plan, mini);
}

t_boolean	trace(t_mini *mini)
{
	t_var_trace	var;;
	t_vec3		ray_direction;

	var.i = 0;
	var.delta_u = 0.0;
	var.delta_v = 0.0;
	while (var.i < HEIGHT)
	{
		var.delta_v = (0.5 - (var.i + 0.5 / HEIGHT))
			* mini->scene.cam[mini->cam_lock].h;
		var.j = 0;
		while (var.j < WIDTH)
		{
			var.delta_u = ((var.j + 0.5 / WIDTH) - 0.5)
				* mini->scene.cam[mini->cam_lock].w;
			get_ray(mini, var.delta_u, var.delta_v, &ray_direction);
			var.j++;
		}
		var.i++;
	}
	return (true);
}
