#include <math.h>
#include "vector.h"

vec3	vec_norm(vec3 v)
{
	float	len;
	vec3	result;

	len = vec_length(v);
	if (len == 0)
		return ((vec3){0, 0, 0});
	result.x = v.x / len;
	result.y = v.y / len;
	result.z = v.z / len;
	return (result);
}
