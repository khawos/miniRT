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
	return ((t_bounds){max, min, 0});
}

/*	0 == left, up, forward
	1 == right, down, backward
*/
// t_bounds	find_bounds(t_bounds old_bounds, int direction)
// {
// 	t_bounds	new_bounds;

// 	printf("%d\n", old_bounds.deepth);
// 	if (old_bounds.max.x - old_bounds.min.x > old_bounds.max.y - old_bounds.min.y && old_bounds.max.y - old_bounds.min.y > old_bounds.max.z - old_bounds.min.z)
// 	{
// 		if (0 == direction)
// 		{
// 			new_bounds.max = (t_vec3){old_bounds.max.x / 2, old_bounds.max.y, old_bounds.max.z};
// 			new_bounds.min = old_bounds.min;
// 			new_bounds.deepth = old_bounds.deepth + 1;
// 		}
// 		else
// 		{
// 			new_bounds.max = old_bounds.max;
// 			new_bounds.min = (t_vec3){old_bounds.max.x / 2, old_bounds.min.y, old_bounds.min.z};
// 			new_bounds.deepth = old_bounds.deepth + 1;
// 		}
// 	}
// 	else if (old_bounds.max.x - old_bounds.min.x < old_bounds.max.y - old_bounds.min.y && old_bounds.max.y - old_bounds.min.y > old_bounds.max.z - old_bounds.min.z)
// 	{
// 		if (0 == direction)
// 		{
// 			new_bounds.max = (t_vec3){old_bounds.max.x, old_bounds.max.y / 2, old_bounds.max.z};
// 			new_bounds.min = old_bounds.min;
// 			new_bounds.deepth = old_bounds.deepth + 1;
// 		}
// 		else
// 		{
// 			new_bounds.max = old_bounds.max;
// 			new_bounds.min = (t_vec3){old_bounds.max.x, old_bounds.min.y / 2, old_bounds.min.z};
// 			new_bounds.deepth = old_bounds.deepth + 1;
// 		}
// 	}
// 	else
// 	{
// 		if (0 == direction)
// 		{
// 			new_bounds.max = (t_vec3){old_bounds.max.x, old_bounds.max.y, old_bounds.max.z / 2};
// 			new_bounds.min = old_bounds.min;
// 			new_bounds.deepth = old_bounds.deepth + 1;
// 		}
// 		else
// 		{
// 			new_bounds.max = old_bounds.max;
// 			new_bounds.min = (t_vec3){old_bounds.max.x, old_bounds.min.y, old_bounds.min.z / 2};
// 			new_bounds.deepth = old_bounds.deepth + 1;
// 		}
// 	}
// 	return (new_bounds);
// }

t_bounds find_bounds(t_bounds old_bounds, int direction)
{
    t_bounds new_bounds;
    double mid_x = (old_bounds.min.x + old_bounds.max.x) / 2.0;
    double mid_y = (old_bounds.min.y + old_bounds.max.y) / 2.0;
    double mid_z = (old_bounds.min.z + old_bounds.max.z) / 2.0;

    double dx = old_bounds.max.x - old_bounds.min.x;
    double dy = old_bounds.max.y - old_bounds.min.y;
    double dz = old_bounds.max.z - old_bounds.min.z;

    if (dx >= dy && dx >= dz) // couper selon X
    {
        if (direction == 0)
        {
            new_bounds.min = old_bounds.min;
            new_bounds.max = (t_vec3){mid_x, old_bounds.max.y, old_bounds.max.z};
        }
        else
        {
            new_bounds.min = (t_vec3){mid_x, old_bounds.min.y, old_bounds.min.z};
            new_bounds.max = old_bounds.max;
        }
    }
    else if (dy >= dx && dy >= dz) // couper selon Y
    {
        if (direction == 0)
        {
            new_bounds.min = old_bounds.min;
            new_bounds.max = (t_vec3){old_bounds.max.x, mid_y, old_bounds.max.z};
        }
        else
        {
            new_bounds.min = (t_vec3){old_bounds.min.x, mid_y, old_bounds.min.z};
            new_bounds.max = old_bounds.max;
        }
    }
    else // couper selon Z
    {
        if (direction == 0)
        {
            new_bounds.min = old_bounds.min;
            new_bounds.max = (t_vec3){old_bounds.max.x, old_bounds.max.y, mid_z};
        }
        else
        {
            new_bounds.min = (t_vec3){old_bounds.min.x, old_bounds.min.y, mid_z};
            new_bounds.max = old_bounds.max;
        }
    }

    new_bounds.deepth = old_bounds.deepth + 1;
    return new_bounds;
}


t_boolean	tr_is_in_bounds(t_objet	tr, t_bounds bounds)
{
	return ((tr.p0.x >= bounds.min.x  && tr.p0.x <= bounds.max.x)
		&& tr.p0.y >= bounds.min.y  && tr.p0.y <= bounds.max.y
		&& tr.p0.z >= bounds.min.z  && tr.p0.z <= bounds.max.z) ||
		((tr.p1.x >= bounds.min.x  && tr.p1.x <= bounds.max.x)
		&& tr.p1.y >= bounds.min.y  && tr.p1.y <= bounds.max.y
		&& tr.p1.z >= bounds.min.z  && tr.p1.z <= bounds.max.z) ||
		((tr.p2.x >= bounds.min.x  && tr.p2.x <= bounds.max.x)
		&& tr.p2.y >= bounds.min.y  && tr.p2.y <= bounds.max.y
		&& tr.p2.z >= bounds.min.z  && tr.p2.z <= bounds.max.z);
}