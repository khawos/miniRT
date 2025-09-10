#include "miniRT.h"

t_inter	intersect_sp(t_mini *mini, t_vec3 ray_direction, t_objet object)
{
	double	b;
	double	c;
	double	delta;

	b = vec_dot(vec_mul_n(ray_direction, 2.0f), vec_substact(mini->scene.cam[mini->cam_lock].pos, object.pos));
	c = powf(vec_get_norme(vec_substact(object.pos, mini->scene.cam[mini->cam_lock].pos)), 2) - powf(object.diameter / 2, 2);

	delta = powf(b, 2) - 4 * c;
	if (delta > 0)
		return (in);
	else if (delta == 0)
		return (edge);
	else if (delta < 0)
		return (out);
	return (out);
}

t_inter	intersect(t_mini *mini, t_vec3 ray_direction, t_objet object)
{
	if (sp == object.type)
		return (intersect_sp(mini, ray_direction, object));
	return (out);
}