#include "vector.h"

vec3	vec_cross(vec3 a, vec3 b)
{
	vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;

	return (result);
}
