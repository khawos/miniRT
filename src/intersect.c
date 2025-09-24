#include "miniRT.h"

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
			//tmp = intersect_cap(origin, ray_direction, &mini->sc.objet[i]);
			//if (tmp > -0.0000000001)
			//	return (true);
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
		if (obj.cap == true)
		{
			P_intersect = vec_add(mini->sc.cam[mini->cam_lock].pos, vec_scale(ray_direction, t));
			obj_to_light = vec_substact(mini->sc.light[1].pos , P_intersect);
			normal = obj.vec_dir;
			result = fabs(vec_dot(normal, vec_normalize(obj_to_light)));
			color = color_scalar(obj.color, result);
			color = color_multiplie(color, apply_ambiant(mini, color));
			color = color_multiplie(color, color_scalar(mini->sc.light[1].color, mini->sc.light[1].ratio));
			return (color);
		}
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
		mini->sc.objet[i].cap = false;
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
			tmp = intersect_cap(mini->sc.cam[mini->cam_lock].pos, ray_direction, &mini->sc.objet[i]);
			if (tmp < t && tmp > 0)
			{
				mini->sc.objet[i].cap = true;
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
