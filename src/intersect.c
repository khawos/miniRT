#include "miniRT.h"

typedef	struct s_equation
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	s1;
	double	s2;

}				t_equation;

double	intersect_sp(t_mini *mini, t_vec3 ray_direction, t_objet *object)
{
	t_equation	var;

	var.a = vec_dot(ray_direction, ray_direction);
	var.b = vec_dot(vec_scale(ray_direction, -2.0),
			vec_substact(object->pos, mini->sc.cam[mini->cam_lock].pos));
	var.c = vec_dot(vec_substact(object->pos, mini->sc.cam[mini->cam_lock].pos),
			vec_substact(object->pos, mini->sc.cam[mini->cam_lock].pos
				)) - pow(object->diameter / 2.0, 2);
	var.delta = pow(var.b, 2) - 4 * var.a * var.c;
	if (var.delta > 0)
	{
		object->color.hit = true;
		var.s1 = (-var.b + sqrt(var.delta)) / (2 * var.a);
		var.s2 = (-var.b - sqrt(var.delta)) / (2 * var.a);
		if (var.s1 > var.s2)
			return (var.s2);
		else
			return (var.s1);
	}
	if (0 == var.delta)
		return (-var.b / (2 * var.a));
	return (-1);	
}

// double intersect_pl(t_mini *mini, t_vec3 ray_direction, t_objet *object)
// {
// 	double	t;

// 	if (vec_dot(object->vec_dir, ray_direction) == 0)
// 	{
// 		if (vec_get_norme(vec_substact(mini->sc.cam[mini->cam_lock].pos, object->pos)) == 0)
// 		{
// 			object->color.hit = true;
// 			return (0);
// 		}
// 		else
// 			return (-1);
// 	}

	
// }

t_color	intersect(t_mini *mini, t_vec3 ray_direction)
{
	double	t;
	double	tmp;
	int		i;
	int		index_tmp;

	i = 0;
	t = 10000;
	tmp = 0; 
	index_tmp = 0;
	while (i < mini->N_OBJ)
	{
		mini->sc.objet[i].color.hit = false;
		if (sp == mini->sc.objet[i].type)
		{
			tmp = intersect_sp(mini, ray_direction, &mini->sc.objet[i]);
			if (tmp < t && tmp > 0)
			{
				t = tmp;
				index_tmp = i;
			}
		}
		if (pl == mini->sc.objet[i].type)
		{
			tmp = intersect_pl(mini, ray_direction, &mini->sc.objet[i]);
		}
		i++;
	}
	return (mini->sc.objet[index_tmp].color);
}
