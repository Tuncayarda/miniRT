#include <math.h>
#include "vector.h"

vec3 vec_negate(vec3 v)
{
	vec3 result;

	result.x = -v.x;
	result.y = -v.y;
	result.z = -v.z;
	return result;
}
