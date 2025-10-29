#include "minirt.h"

t_color	reflection(t_mini *mini, t_ray *old_ray, t_objet obj, t_normal n)
{
	t_color	bounce_color;
	t_vec3	normal;
	t_ray	ray_bounce;

	if (is_null_vector(n.texture))
		normal = n.geometric;
	else
		normal = n.texture;
	if (old_ray->bounce >= BOUNCE_MAX)
		return (old_ray->color);
	if (obj.type != sp)
		return (old_ray->color);
	ray_bounce.origin = vec_add(old_ray->origin, vec_scale(old_ray->dir, old_ray->t));
	ray_bounce.bounce = old_ray->bounce + 1;
	ray_bounce.dir = vec_normalize(vec_substact(old_ray->dir, vec_scale(normal, 2 * vec_dot(old_ray->dir, normal))));
	bounce_color = mix_colors_ratio(intersect_loop(mini, &ray_bounce), old_ray->color, 0.5);
	return (bounce_color);
}
