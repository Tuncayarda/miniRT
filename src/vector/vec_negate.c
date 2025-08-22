#include <math.h>
#include "vector.h"

t_vec3	vec_negate(t_vec3 v)
{
	t_vec3	result;

	result.x = -v.x;
	result.y = -v.y;
	result.z = -v.z;
	return (result);
}
