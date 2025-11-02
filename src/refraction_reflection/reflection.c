/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:46:14 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/01 17:06:12 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

extern int wtf_bool;

t_color	reflection(t_mini *mini, t_ray *old_ray, t_objet obj, t_normal n)
{
	t_color	bounce_color;
	t_vec3	normal;
	t_ray	ray_bounce;
	double	roughness;

	roughness = get_roughness_from_map(obj, obj.roughness_default, n.geometric);
	if (!roughness)
		return (old_ray->color);
	if (is_null_vector(n.texture))
		normal = n.geometric;
	else
		normal = n.texture;
	// if (obj.id == 6)
	// {
	// 	printf("old : %d\n", old_ray->bounce); 
	// }
	if (old_ray->bounce >= BOUNCE_MAX)
		return (old_ray->color);
	ray_bounce.origin = vec_add(old_ray->origin, vec_scale(old_ray->current_dir,
				old_ray->t));
	ray_bounce.origin = vec_add(ray_bounce.origin, vec_scale(vec_invert(old_ray->current_dir), 1.0001));
	ray_bounce.bounce = old_ray->bounce + 1;
	ray_bounce.current_dir = vec_normalize(vec_substact
			(old_ray->current_dir, vec_scale(normal, 2
					* vec_dot(old_ray->current_dir, normal))));
	bounce_color = mix_colors_ratio(intersect_loop(mini, &ray_bounce),
			old_ray->color, roughness);
	if (ray_bounce.t == -1)
		old_ray->t = -1;
	return (bounce_color);
}
