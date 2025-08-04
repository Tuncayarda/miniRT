#include <math.h>
#include "vector.h"

float	vec_length(vec3 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}
