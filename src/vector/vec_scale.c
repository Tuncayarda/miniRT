#include "vector.h"

vec3	vec_scale(vec3 v, float s)
{
	vec3	result;

	result.x = v.x * s;
	result.y = v.y * s;
	result.z = v.z * s;
	return (result);
}