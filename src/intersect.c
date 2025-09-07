#include "miniRT.h"

t_inter	intersect_sp(t_mini *mini, t_vec3 ray_direction, t_objet object)
{
	double	b;
	double	c;
	double	delta;

	b = 2 * (vec_dot(ray_direction, vec_substact(mini->scene.cam[mini->cam_lock].pos, object.pos)));
	c = vec_dot(vec_substact(mini->scene.cam[mini->cam_lock].pos, object.pos), vec_substact(mini->scene.cam[mini->cam_lock].pos, object.pos)) - powf((object.diameter / 2), 2);

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