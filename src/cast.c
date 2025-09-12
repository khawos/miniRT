/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:22:31 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/12 13:34:55 by amedenec         ###   ########.fr       */
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
	//printf(" x : %f, y : %f, z : %f\n", mini->sc.cam[mini->cam_lock].pos.x, mini->sc.cam[mini->cam_lock].pos.y, mini->sc.cam[mini->cam_lock].pos.z);
	
	P->x = mini->sc.cam[mini->cam_lock].pos.x + 
		mini->sc.cam[mini->cam_lock].vec_dir.x + 
			(mini->sc.cam[mini->cam_lock].right.x * d_u) + 
				(mini->sc.cam[mini->cam_lock].up.x * d_v);
	P->y = mini->sc.cam[mini->cam_lock].pos.y + 
		mini->sc.cam[mini->cam_lock].vec_dir.y + 
			(mini->sc.cam[mini->cam_lock].right.y * d_u) + 
				(mini->sc.cam[mini->cam_lock].up.y * d_v);
	P->z = mini->sc.cam[mini->cam_lock].pos.z + 
		mini->sc.cam[mini->cam_lock].vec_dir.z + 
			(mini->sc.cam[mini->cam_lock].right.z * d_u) + 
				(mini->sc.cam[mini->cam_lock].up.z * d_v);
	//printf("Pixel in space \n x : %f, y : %f,  : %f\n", P->x, P->y, P->z);				
	//printf("u : %f, v : %f\n", d_u, d_v);
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

	ray_D->x = P->x - mini->sc.cam[mini->cam_lock].pos.x;
	ray_D->y = P->y - mini->sc.cam[mini->cam_lock].pos.y;
	ray_D->z = P->z - mini->sc.cam[mini->cam_lock].pos.z;
	norme_ray_D = vec_get_norme(*ray_D);
	if (norme_ray_D  != 0)
	{
		ray_D->x = ray_D->x / norme_ray_D;
		ray_D->y = ray_D->y / norme_ray_D;
		ray_D->z = ray_D->z / norme_ray_D;
	}
}

void	get_ray(t_mini *mini, double d_u, double d_v, t_vec3 *ray_dir)
{
	t_vec3		pixel_on_project_plan;

	get_pixel_in_space(&pixel_on_project_plan, d_u, d_v, mini);
//	printVec(pixel_on_project_plan);
//	get_ray_direction(ray_dir, &pixel_on_project_plan, mini);
	ray_dir->x = pixel_on_project_plan.x;
	ray_dir->y = pixel_on_project_plan.y;
	ray_dir->z = pixel_on_project_plan.z;
}

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
/*
* @brief
* premier rayon en haut a gauche du plan projete. 

	On addition la pos de la cam + la direction puis on bouge vers le haut up de la hauteur / 2, et puis vers la gauche en faisant - right de w / 2 de distance. 

	Je sais ca parrait illisible.
*/
t_vec3	get_left_corner_viewport(t_mini *mini)
{
	t_vec3	result;
	t_cam	cam;

	cam = mini->sc.cam[mini->cam_lock];
	result.x = cam.pos.x + cam.vec_dir.x +
		(cam.up.x * (cam.h / 2.0f)) - 
			(cam.right.x * (cam.w / 2.0f));
	result.y = cam.pos.y + cam.vec_dir.y +
	(cam.up.y * (cam.h / 2.0f)) - 
		(cam.right.y* (cam.w / 2.0f));
	result.z = cam.pos.z + cam.vec_dir.z +
	(cam.up.z* (cam.h / 2.0f)) - 
		(cam.right.z * (cam.w / 2.0f));
	return (result);
}

t_boolean	cast(t_mini *mini)
{
	t_var_trace	var;
	t_vec3		ray_direction;

	var.i = 0;
	var.delta_u = 0;
	while (var.i < HEIGHT)
	{
		var.j = 0;
		var.delta_v = 0;
		ray_direction = get_left_corner_viewport(mini);
		ray_direction = vec_substact(ray_direction, vec_scale(mini->sc.cam[mini->cam_lock].up, var.delta_u));
		while (var.j < WIDTH)
		{
			clash_of_clan(mini, vec_normalize(vec_add(ray_direction, vec_scale(mini->sc.cam[mini->cam_lock].right, var.delta_v))), var.j, var.i);
			var.j++;
			var.delta_v = var.delta_v + (mini->sc.cam[mini->cam_lock].w / (double)WIDTH);
		}
		var.delta_u = var.delta_u + (mini->sc.cam[mini->cam_lock].h / (double)HEIGHT);
		var.i++;
	}
	return (true);
}
