#include "minirt.h"

t_vec3	vec_invert(t_vec3 vec)
{
	return ((t_vec3){-vec.x, -vec.y, -vec.z});	
}
