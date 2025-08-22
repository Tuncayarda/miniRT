#include <math.h>
#include "vector.h"

t_vec3	vec_norm(t_vec3 v)
{
	float	len;
	t_vec3	result;

	len = vec_length(v);
	if (len == 0)
		return (vec_gen(0, 0, 0));
	result.x = v.x / len;
	result.y = v.y / len;
	result.z = v.z / len;
	return (result);
}
