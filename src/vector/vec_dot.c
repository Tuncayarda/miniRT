#include <math.h>
#include "vector.h"

float	vec_dot(vec3 a, vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
