#include "vector.h"

t_vec3	vec_scale(t_vec3 v, float s)
{
	t_vec3	result;

	result.x = v.x * s;
	result.y = v.y * s;
	result.z = v.z * s;
	return (result);
}
