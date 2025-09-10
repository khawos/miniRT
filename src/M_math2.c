#include "miniRT.h"

double	vec_dot(t_vec3 i, t_vec3 j)
{
	return (i.x * j.x + i.y * j.y + i.z * j.y);
}

t_vec3	vec_substact(t_vec3 i, t_vec3 j)
{
	t_vec3 result;
	result.x = i.x - j.x; 
	result.y = i.y - j.y; 
	result.z = i.z - j.z;
	return (result); 
}

t_vec3	vec_add(t_vec3 i, t_vec3 j)
{
	t_vec3 result;

	result.x = i.x + j.x; 
	result.y = i.y + j.y; 
	result.z = i.z + j.z;
	return (result); 
}

void	vec_add_ptr(t_vec3 *result, t_vec3 add)
{
	result->x += add.x;
	result->y += add.y;
	result->z += add.z;
}

void	vec_sub_ptr(t_vec3 *result, t_vec3 sub)
{
	result->x -= sub.x;
	result->y -= sub.y;
	result->z -= sub.z;
}

t_vec3	vec_normalize(t_vec3 i)
{

	t_vec3	result;
	double	norme;

	norme = vec_get_norme(i);
	result.x = i.x / norme;
	result.y = i.y / norme;
	result.z = i.z / norme;
	return (result);
}

t_vec3	vec_mul_n(t_vec3 i, double n)
{
	t_vec3	result;

	result.x = i.x * n;
	result.y = i.y * n;
	result.z = i.z * n;
	return (result);
}