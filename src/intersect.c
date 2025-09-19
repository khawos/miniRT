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

double	intersect_sp(t_vec3 origin, t_vec3 ray_direction, t_objet *object)
{
	t_equation	var;

	var.a = vec_dot(ray_direction, ray_direction);
	var.b = vec_dot(vec_scale(ray_direction, -2.0),
			vec_substact(object->pos, origin));
	var.c = vec_dot(vec_substact(object->pos, origin),
			vec_substact(object->pos, origin
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

// double intersect_pl(t_vec3 origin, t_vec3 ray_direction, t_objet *object)
// {
// 	double	t;

// 	if (vec_dot(vec_normalize(origin), object->vec_dir) == 0)
// 	{
// 		if (vec_dot(vec_substact(object->pos, origin), object->vec_dir) == 0)
// 		{
// 			object->color.hit = true;
// 			return (0);
// 		}
// 		else
// 			return (-1);
// 	}
// 	object->color.hit = true;
// 	t = vec_dot(vec_substact(object->pos, origin), object->vec_dir) / vec_dot(vec_normalize(origin), object->vec_dir);
// 	return (t); 
	
// }

t_boolean is_intersect(t_mini *mini, t_vec3 ray_direction, t_vec3 origin)
{
	double		tmp;
	int			i;

	
	i = 0;
	tmp = 0; 
	while (i < mini->N_OBJ)
	{
		mini->sc.objet[i].color.hit = false;
		if (sp == mini->sc.objet[i].type)
		{
			tmp = intersect_sp(origin, ray_direction, &mini->sc.objet[i]);
			if (tmp > -0.0000000001)
				return (true);
		}
		// if (pl == mini->sc.objet[i].type)
		// {
		// 	tmp = intersect_pl(origin, ray_direction, &mini->sc.objet[i]);
		// 	if (tmp > 0)
		// 		return (true);
		// }
		i++;
	}
	return (false);
}

t_boolean	shadow_ray(t_mini *mini, t_vec3 ray_direction, double t)
{
	t_vec3		secondary_ray;
	t_vec3		P_intersect;
	t_boolean	result;

	P_intersect = vec_scale(ray_direction, t);
	secondary_ray = vec_substact(mini->sc.light[1].pos , P_intersect);
	result = is_intersect(mini, vec_normalize(secondary_ray), P_intersect);
	return (result);
}

t_color	light_ray(t_mini *mini, t_vec3 ray_direction, double t, t_objet obj)
{
	t_vec3	obj_to_light;
	t_vec3	P_intersect;
	t_vec3	normal;
	double	result;
	t_color	color;

	P_intersect = vec_scale(ray_direction, t);
	obj_to_light = vec_substact(mini->sc.light[1].pos , obj.pos);
	normal = vec_normalize(vec_substact(P_intersect, obj.pos));
	result = vec_dot(vec_normalize(normal), vec_normalize(obj_to_light));
	if (result < 0)
		result = 0;
	color = color_scalar(obj.color, result);
	return (color);
}

t_color	intersect(t_mini *mini, t_vec3 ray_direction)
{
	double		t;
	double		tmp;
	int			i;
	int			index_tmp;
	t_color		result;

	i = 0;
	t = 10000;
	tmp = 0; 
	index_tmp = 0;
	result = (t_color){0,0,0,1};
	while (i < mini->N_OBJ)
	{
		mini->sc.objet[i].color.hit = false;
		if (sp == mini->sc.objet[i].type)
		{
			tmp = intersect_sp(mini->sc.cam[mini->cam_lock].pos, ray_direction, &mini->sc.objet[i]);
			if (tmp < t && tmp > 0)
			{
				t = tmp;
				index_tmp = i;
			}
		}
		i++;
	}
	//if (shadow_ray(mini, ray_direction, t) && mini->sc.objet[index_tmp].color.hit == true)
	//	return (result);
	if (mini->sc.objet[index_tmp].color.hit == true)
		return (light_ray(mini, ray_direction,t , mini->sc.objet[index_tmp]));
	return (mini->sc.objet[index_tmp].color);
}
