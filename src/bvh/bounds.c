#include "minirt.h"

static t_vec3	try_max_bound(t_objet obj, t_vec3 max)
{
	if (obj.p0.x > max.x)
		max.x = obj.p0.x;
	if (obj.p0.y > max.y)
		max.y = obj.p0.y;
	if (obj.p0.z > max.z)
		max.z = obj.p0.z;
	if (obj.p1.x > max.x)
		max.x = obj.p1.x;
	if (obj.p1.y > max.y)
		max.y = obj.p1.y;
	if (obj.p1.z > max.z)
		max.z = obj.p1.z;	
	if (obj.p2.x > max.x)
		max.x = obj.p2.x;
	if (obj.p2.y > max.y)
		max.y = obj.p2.y;
	if (obj.p2.z > max.z)
		max.z = obj.p2.z;
	return (max);
}

static t_vec3	try_min_bound(t_objet obj, t_vec3 min)
{
	if (obj.p0.x < min.x)
		min.x = obj.p0.x;
	if (obj.p0.y < min.y)
		min.y = obj.p0.y;
	if (obj.p0.z < min.z)
		min.z = obj.p0.z;
	if (obj.p1.x < min.x)
		min.x = obj.p1.x;
	if (obj.p1.y < min.y)
		min.y = obj.p1.y;
	if (obj.p1.z < min.z)
		min.z = obj.p1.z;
	if (obj.p2.x < min.x)
		min.x = obj.p2.x;
	if (obj.p2.y < min.y)
		min.y = obj.p2.y;
	if (obj.p2.z < min.z)
		min.z = obj.p2.z;
	return (min);
}

t_bounds	found_first_bound(t_mini *mini)
{
	t_objet obj;
	t_vec3	max;
	t_vec3	min;
	int	i;
	i = 0;
	max = vec_create(-RENDER_DISTANCE, -RENDER_DISTANCE, -RENDER_DISTANCE);
	min = vec_create(RENDER_DISTANCE, RENDER_DISTANCE, RENDER_DISTANCE);
	while (i < mini->N_OBJ)
	{
		obj = mini->sc.objet[i];
		if (tr == obj.type) // on trouve le max
		{
			max = try_max_bound(obj, max);
			min = try_min_bound(obj, min);
		}
		i++;
	}
	return ((t_bounds){max, min});
}