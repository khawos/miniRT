/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:40:06 by jbayonne          #+#    #+#             */
/*   Updated: 2025/12/10 18:04:39 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec2	get_uv_sp(t_vec3 normal, t_vec2 size)
{
	t_vec2	texture;
	double	phi;
	double	theta;

	phi = atan2(normal.z, normal.x);
	theta = acos(normal.y);
	texture.u = ((-phi + M_PI) / (2 * M_PI)) * (size.u - 1);
	texture.v = (theta / M_PI) * (size.v - 1);
	return (texture);
}

#include <math.h>

t_vec2  get_uv_pl(t_vec3 normal, t_vec2 size, t_vec3 p)
{
    t_vec3  u_axis;
    t_vec3  v_axis;
    t_vec2  uv;
	double	u;
	double	v;
    
    // 1. GENERATION DU SYSTEME DE COORDONNEES (BASIS)
    // On doit trouver un vecteur arbitraire qui n'est pas parallèle à la normale
    // Si la normale pointe vers le haut (0, 1, 0), on utilise l'axe X (1, 0, 0)
    // Sinon, on utilise un vecteur arbitraire comme (0, 1, 0) "UP"
    t_vec3 world_up = {0, 1, 0};
    
    // Si la normale est trop proche de l'axe Y (verticale), on change d'axe de référence
    // pour éviter que le produit vectoriel ne donne 0.
    if (fabs(normal.y) > 0.9)
        world_up = (t_vec3){0, 0, 1};

    // Produit vectoriel pour avoir l'axe U (tangente) perpendiculaire à la normale
    u_axis = vec_normalize(vec_cross(normal, world_up));
    
    // Produit vectoriel pour avoir l'axe V (bitangente) perpendiculaire aux deux autres
    v_axis = vec_normalize(vec_cross(normal, u_axis));

    // 2. PROJECTION (Passage de 3D à 2D)
    // On projette le point P sur nos nouveaux axes 2D
    double raw_u = vec_dot(u_axis, p);
    double raw_v = vec_dot(v_axis, p);

    // 3. TILING (La répétition)
    // Disons qu'on veut que la texture se répète toutes les 10 unités (scale)
    double scale = 300; 
    
    // Le modulo permet de garder u et v entre 0 et 1 (coordonnées UV standard)
    // L'astuce mathématique ici gère les nombres négatifs correctement
    u = raw_u / scale;
    u = u - floor(u); 

    v = raw_v / scale;
    v = v - floor(v);

	uv.u = u * size.u;
	uv.v = v * size.v;
    return (uv);
}
