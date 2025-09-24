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
		if (var.s1 < 0 && var.s2 < 0)
			return (object->color.hit = false, -1);
		if (var.s1 > var.s2)
			return (var.s2);
		else
			return (var.s1);
	}
	if (0 == var.delta)
		return (-var.b / (2 * var.a));
	return (-1);	
}

double intersect_pl(t_vec3 origin, t_vec3 ray_direction, t_objet *object)
{
	double	t;

	object->color.hit = true;
	object->vec_dir = vec_normalize(object->vec_dir);
	if (vec_dot(ray_direction, object->vec_dir) == 0)
		return (object->color.hit = false, 0);
	t = vec_dot(vec_substact(object->pos, origin), object->vec_dir) / vec_dot(ray_direction, object->vec_dir);
	if (t < 0)
		object->color.hit = false;
	return (t);
}

double	intersect_cy(t_vec3 origin, t_vec3 ray_direction, t_objet *object)
{
	double	a;
	double	b;
	double	c;
	double	s1;
	double	s2;
	double delta;
	
	t_vec3	intersect;
	t_vec3	H;
	t_vec3	B;
	t_vec3	H_chapeau;
	t_vec3	W;


// CYLINDER

	B = vec_substact(object->pos, vec_scale(object->vec_dir, object->height / 2));
	W = vec_substact(origin, B);
	H = vec_add(object->pos, vec_scale(object->vec_dir, object->height / 2));
	H_chapeau = vec_div(vec_substact(H, B), vec_get_norme(vec_substact(H, B)));


	a = vec_dot(ray_direction, ray_direction) - pow(vec_dot(ray_direction, H_chapeau), 2);
	
	b = 2 * (vec_dot(ray_direction, W) - vec_dot(ray_direction , H_chapeau) * vec_dot(W, H_chapeau));

	c = vec_dot(W, W) - pow(vec_dot(W, H_chapeau), 2) - pow(object->diameter / 2, 2);

	delta = pow(b, 2) - 4 * a * c;
	if ( delta > 0)
	{

		object->color.hit = true;
		s1 = (-b + sqrt(delta)) / (2 * a);
		s2 = (-b - sqrt(delta)) / (2 * a);
		if ((s1 < 0 && s2 < 0))
			return (object->color.hit = false, -1);
		if (s1 > s2)
		{
			intersect = vec_add(origin, vec_scale(ray_direction, s2));
			intersect = vec_substact(intersect, B);
			if (vec_dot(intersect, object->vec_dir) < 0 || vec_dot(intersect, object->vec_dir) > object->height)
				return (object->color.hit = false, -1);
			return (s2);
		}	
		else
		{
			intersect = vec_add(origin, vec_scale(ray_direction, s1));
			intersect = vec_substact(intersect, B);
			if (vec_dot(intersect, object->vec_dir) < 0 || vec_dot(intersect, object->vec_dir) > object->height)
				return (object->color.hit = false, -1);
			return (s1);
		}
	}
	if (0 == delta)
		return (-b / (2 * a));
	return (-1);	

}

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
		if (cy == mini->sc.objet[i].type)
		{
			tmp = intersect_cy(origin, ray_direction, &mini->sc.objet[i]);
			if (tmp > -0.0000000001)
				return (true);
		}
		i++;
	}
	return (false);
}

t_boolean	shadow_ray(t_mini *mini, t_vec3 ray_direction, double t)
{
	t_vec3		secondary_ray;
	t_vec3		P_intersect;
	t_boolean	result;

	P_intersect = vec_add(mini->sc.cam[mini->cam_lock].pos, vec_scale(ray_direction, t));
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

	if (obj.type == sp)
	{
		P_intersect = vec_add(mini->sc.cam[mini->cam_lock].pos, vec_scale(ray_direction, t));
		obj_to_light = vec_substact(mini->sc.light[1].pos , obj.pos);
		normal = vec_normalize(vec_substact(P_intersect, obj.pos));
		result = vec_dot(vec_normalize(normal), vec_normalize(obj_to_light));
		if (result < 0)
			result = 0;
		color = color_scalar(obj.color, result);
	}
	if (obj.type == pl)
	{
		
		if (shadow_ray(mini, ray_direction, t))
			return ((t_color){0,0,0,1});
		P_intersect = vec_add(mini->sc.cam[mini->cam_lock].pos, vec_scale(ray_direction, t));
		obj_to_light = vec_substact(mini->sc.light[1].pos , P_intersect);
		normal = obj.vec_dir;
		result = fabs(vec_dot(normal, vec_normalize(obj_to_light)));
		color = color_scalar(obj.color, result);
	}
	if (obj.type == cy)
	{
		t_vec3	base;

		P_intersect = vec_add(mini->sc.cam[mini->cam_lock].pos, vec_scale(ray_direction, t));
		obj_to_light = vec_substact(mini->sc.light[1].pos , P_intersect);
		base = vec_substact(obj.pos, vec_scale(obj.vec_dir, obj.height / 2));
		normal = vec_normalize(vec_substact( P_intersect, (vec_add(base, vec_scale(obj.vec_dir, vec_dot( vec_substact(P_intersect, base),obj.vec_dir))))));
		result = vec_dot(normal, vec_normalize(obj_to_light));
		if (result < 0)
			result = 0;
		color = color_scalar(obj.color, result);
	}
	color = color_multiplie(color, apply_ambiant(mini, color));
	color = color_multiplie(color, color_scalar(mini->sc.light[1].color, mini->sc.light[1].ratio));
	return (color);
}

t_color	intersect(t_mini *mini, t_vec3 ray_direction)
{
	double		t;
	double		tmp;
	int			i;
	int			index_tmp;

	i = 0;
	t = 10000;
	tmp = 0; 
	index_tmp = 0;
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
		if (pl == mini->sc.objet[i].type)
		{
			tmp = intersect_pl(mini->sc.cam[mini->cam_lock].pos, ray_direction, &mini->sc.objet[i]);
			if (tmp < t && tmp > 0)
			{
				t = tmp;
				index_tmp = i;
			}
		}
		if (cy == mini->sc.objet[i].type)
		{
			tmp = intersect_cy(mini->sc.cam[mini->cam_lock].pos, ray_direction, &mini->sc.objet[i]);
			if (tmp < t && tmp > 0)
			{
				t = tmp;
				index_tmp = i;
			}
		}
		i++;
	}
	if (mini->sc.objet[index_tmp].color.hit == true)
		return (light_ray(mini, ray_direction,t , mini->sc.objet[index_tmp]));
	return (mini->sc.objet[index_tmp].color);
}
