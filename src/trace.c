/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:22:31 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/07 21:49:07 by amedenec         ###   ########.fr       */
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
	//printf(" x : %f, y : %f, z : %f\n", mini->scene.cam[mini->cam_lock].pos.x, mini->scene.cam[mini->cam_lock].pos.y, mini->scene.cam[mini->cam_lock].pos.z);
	
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

	ray_D->x = P->x - mini->scene.cam[mini->cam_lock].pos.x;
	ray_D->y = P->y - mini->scene.cam[mini->cam_lock].pos.y;
	ray_D->z = P->z - mini->scene.cam[mini->cam_lock].pos.z;
	norme_ray_D = vec_normalize(*ray_D);
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
	(void)x;
	(void)y;
	while (i < mini->N_OBJ)
	{
		k = intersect(mini, ray_direction, mini->scene.objet[i]);
		if (k == out)
			my_mlx_pixel_put(mini, x, y, 0xFFFFFF);
		if (k == in)
			my_mlx_pixel_put(mini, x, y, color_shift(mini->scene.objet[i].color));			
		else if (k == edge)
			my_mlx_pixel_put(mini, x, y,(unsigned int)6579300);			
		i++;
	}
}
/*
* @brief
* premier rayon en haut a gauche du plan projete. 

	On addition la pos de la cam + la direction puis on bouge vers le haut up de la hauteur / 2, et puis vers la gauche en faisant - right de w / 2 de distance. 

	Je sais ca parrait illisible.
*/
void	get_p_0(t_vec3 *p0, t_mini *mini)
{
	p0->x = mini->scene.cam[mini->cam_lock].pos.x + mini->scene.cam[mini->cam_lock].vec_dir.x +
		(mini->scene.cam[mini->cam_lock].up.x * (mini->scene.cam[mini->cam_lock].h / 2.0f)) - 
			(mini->scene.cam[mini->cam_lock].right.x * (mini->scene.cam[mini->cam_lock].w / 2.0f));

	p0->y = mini->scene.cam[mini->cam_lock].pos.y + mini->scene.cam[mini->cam_lock].vec_dir.y +
	(mini->scene.cam[mini->cam_lock].up.y * (mini->scene.cam[mini->cam_lock].h / 2.0f)) - 
		(mini->scene.cam[mini->cam_lock].right.y* (mini->scene.cam[mini->cam_lock].w / 2.0f));

	p0->z = mini->scene.cam[mini->cam_lock].pos.z + mini->scene.cam[mini->cam_lock].vec_dir.z +
	(mini->scene.cam[mini->cam_lock].up.z* (mini->scene.cam[mini->cam_lock].h / 2.0f)) - 
		(mini->scene.cam[mini->cam_lock].right.z * (mini->scene.cam[mini->cam_lock].w / 2.0f));
}

t_boolean	trace(t_mini *mini)
{
	t_var_trace	var;
	//t_vec3		ray_direction;
	t_vec3		P_0;

	var.i = 0;
	var.delta_u = 0.0;
	var.delta_v = 0.0;
	get_p_0(&P_0, mini);
	printVec(P_0);
	while ( var.i < HEIGHT)
	{
		var.j = 0;
		var.delta_v = 0;
		while (var.j < WIDTH)
		{
		//	printf(" u : %f, v ; %f\n", var.delta_u, var.delta_v);
			var.j++;
			var.delta_v = var.delta_v + (mini->scene.cam[mini->cam_lock].w / (double)WIDTH);
		}
		var.delta_u = var.delta_u + (mini->scene.cam[mini->cam_lock].h / (double)HEIGHT);
		var.i++;
	}
	return (true);
}
