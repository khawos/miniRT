/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:46:14 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/02 13:09:43 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_color	refract_or_reflect(t_mini *mini, t_ray *old_ray, t_objet obj, t_normal n)
{
	t_color	color;
	t_vec3	normal;

	normal = n.texture;
	if (is_null_vector(n.texture))
		normal = n.geometric;
	if (obj.mat.ior)
		color = refraction(old_ray, mini, obj, normal);
	else
		color = reflection(mini, old_ray, obj, n);
	return (color);
}

t_color	reflection(t_mini *mini, t_ray *old_ray, t_objet obj, t_normal n)
{
	t_color	bounce_color;
	t_vec3	normal;
	t_ray	ray_bounce;
	double	roughness;

	ray_bounce.origin = vec_add(old_ray->origin, vec_scale(old_ray->current_dir,
				old_ray->t));
	ray_bounce.origin = vec_add(ray_bounce.origin, vec_scale(
				vec_invert(old_ray->current_dir), 1.0001));
	roughness = get_roughness_from_map(obj, obj.roughness_default, n.geometric, ray_bounce.origin);
	if (!roughness)
		return (old_ray->color);
	normal = n.texture;
	if (is_null_vector(n.texture))
		normal = n.geometric;
	if (old_ray->bounce >= BOUNCE_MAX)
		return (old_ray->color);
	ray_bounce.bounce = old_ray->bounce + 1;
	ray_bounce.current_dir = vec_normalize(vec_substact(old_ray->current_dir,
				vec_scale(normal, 2 * vec_dot(old_ray->current_dir, normal))));
	bounce_color = mix_colors_ratio(intersect_loop(mini, &ray_bounce),
			old_ray->color, roughness);
	if (ray_bounce.t == -1)
		old_ray->t = -1;
	return (bounce_color);
}

t_color refraction(t_ray *old_ray, t_mini *mini, t_objet obj, t_vec3 normal)
{
    t_ray   refract_ray;
    t_vec3  ray_perp;
    t_vec3  ray_para;
    t_color color;
    
    t_vec3 unit_dir = vec_normalize(old_ray->current_dir);
    
    // --- CORRECTION 1 : GESTION ENTREE / SORTIE ---
    // On vérifie si le rayon est en train d'entrer ou de sortir
    // Si le dot product est > 0, le rayon et la normale vont dans le même sens -> on est dedans, on sort.
    double cos_theta;
    t_vec3 outward_normal;
    double refraction_ratio;

    // Ton IOR cible (ex: 1.5 pour verre, 1.0 pour air)
    double target_ior = 1.25; 

    if (vec_dot(unit_dir, normal) > 0.0) {
        // SORTIE : On est dans la boule, on sort vers l'air
        outward_normal = vec_invert(normal);   // On retourne la normale pour qu'elle fasse face au rayon
        refraction_ratio = target_ior;         // (Glass -> Air) : n_glass / n_air = 1.5 / 1.0 => on inverse selon ta logique math
        // Note: La convention habituelle est ratio = etai / etat.
        // Si on sort (Verre -> Air): ratio = 1.5 / 1.0. 
        // ATTENTION : Ta formule math assume ratio = n1/n2. 
        // Vérifions ta formule : R_perp = ratio * ... 
        // Pour sortir, le rayon doit s'écarter, le ratio doit être > 1 (ex: 1.5).
        // Pour entrer, ratio < 1 (ex: 1/1.5).
        refraction_ratio = target_ior; // Si target_ior est l'indice du verre (1.5), ici on mettrait l'indice lui-même.
    } else {
        // ENTREE : Air -> Verre
        outward_normal = normal;
        refraction_ratio = 1.0 / target_ior;
    }

    // Avec IOR = 1.0, refraction_ratio sera 1.0 dans les deux cas.
    
    // Recalcul du cos_theta avec la bonne normale
    cos_theta = fmin(vec_dot(vec_invert(unit_dir), outward_normal), 1.0);

    // --- FIN CORRECTION 1 ---

    if (old_ray->bounce >= BOUNCE_MAX || obj.type != sp)
        return (old_ray->color);

    // Calcul Perpendiculaire
    t_vec3 r_plus_cosn = vec_add(unit_dir, vec_scale(outward_normal, cos_theta));
    ray_perp = vec_scale(r_plus_cosn, refraction_ratio);

    // Calcul Parallèle
    double perp_len_sq = vec_dot(ray_perp, ray_perp);
    double discriminant = 1.0 - perp_len_sq;

    // Total Internal Reflection (ne devrait pas arriver avec IOR 1.0)
    if (discriminant < 0) {
        // Ici, il faudrait normalement retourner une REFLEXION (miroir)
        // Pour l'instant, on return du noir ou la couleur de l'objet pour debugger
        return ((t_color){0, 0, 0}); 
    }
    
    ray_para = vec_scale(outward_normal, -sqrt(discriminant));
    
    // Construction du rayon
    refract_ray.bounce = old_ray->bounce + 1;
    refract_ray.current_dir = vec_normalize(vec_add(ray_perp, ray_para));

    // --- CORRECTION 2 : SELF-INTERSECTION (ACNE) ---
    // On calcule le point d'impact exact
    t_vec3 hit_point = vec_add(old_ray->origin, vec_scale(old_ray->current_dir, old_ray->t));
    
    // On décale la nouvelle origine un tout petit peu dans la direction du rayon réfracté
    // EPSILON est une petite valeur genre 0.001 ou 1e-4 définie dans ton .h
    t_vec3 offset = vec_scale(refract_ray.current_dir, 1e-4); 
    refract_ray.origin = vec_add(hit_point, offset);
    // -----------------------------------------------

    color = intersect_loop(mini, &refract_ray);
    // Note: j'ai enlevé le mix_colors_ratio pour tester la transparence pure.
    // Si IOR = 1.0, tu veux voir 100% de la couleur retournée.
    
    return (color);
}