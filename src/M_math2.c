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