#include "vector.h"

vec3	vec_add(vec3 a, vec3 b)
{
	vec3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}
