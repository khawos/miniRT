#include "minirt.h"

t_color	refration(t_mini *mini, t_ray old_ray, double t, t_objet obj, t_color first_ray_color)
{
	t_color	bounce_color;
	t_vec3	p;
	t_vec3	to_light;
	double	dot;
	t_var_texture	var;
	t_ray			ray_bounce;

	if (obj.type != sp)
		return (first_ray_color);

	p = vec_add(old_ray.origin, vec_scale(old_ray.dir, t));
	to_light = vec_substact(mini->sc.light[1].pos, obj.pos);
	var = find_ray_texture(obj, p);
	ray_bounce.origin = p;
	ray_bounce.dir = vec_substact(old_ray.dir, vec_scale(var.normal, 2 * vec_dot(old_ray.dir, var.normal)));
	bounce_color = mix_colors_ratio(intersect_loop(mini, ray_bounce, &t), first_ray_color, 1);
	return (bounce_color);
}
