#include "minirt.h"

t_color	refration(t_mini *mini, t_vec3 ray_dir, double t, t_objet obj, t_color first_ray_color)
{
	t_vec3	p;
	t_vec3	to_light;
	double	dot;
	t_var_texture	var;
	t_vec3	ray_dir_bounce;

	if (obj.type != sp)
		return (first_ray_color);

	p = vec_add(mini->sc.cam[mini->cam_lock].pos, vec_scale(ray_dir, t));
	to_light = vec_substact(mini->sc.light[1].pos, obj.pos);
	var = find_ray_texture(obj, p);
	ray_dir_bounce = vec_substact(ray_dir, vec_scale(var.normal, 2 * vec_dot(ray_dir, var.normal)));
	return (intersect_loop(mini, ray_dir_bounce, &t));
}
