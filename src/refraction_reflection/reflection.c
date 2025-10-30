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
	ray_bounce.origin = vec_add(old_ray->origin, vec_scale(old_ray->current_dir, old_ray->t));
	ray_bounce.bounce = old_ray->bounce + 1;
	ray_bounce.current_dir = vec_normalize(vec_substact(old_ray->current_dir, vec_scale(normal, 2 * vec_dot(old_ray->current_dir, normal))));
	bounce_color = mix_colors_ratio(intersect_loop(mini, &ray_bounce), old_ray->color, 0);
	if (ray_bounce.t == -1)
		old_ray->t = -1;
	return (bounce_color);
}
