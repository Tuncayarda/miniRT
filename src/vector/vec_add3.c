#include "vector.h"

vec3	vec_add3(vec3 a, vec3 b, vec3 c)
{
	vec3	result;

	result.x = a.x + b.x + c.x;
	result.y = a.y + b.y + c.y;
	result.z = a.z + b.z + c.z;
	return (result);
}
