#include <math.h>
#include "render.h"

bool	solve_quadratic(float a, float b, float c, float *t)
{
	float	discriminant;
	float	temp;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	temp = (-b - sqrtf(discriminant)) / (2.0f * a);
	if (temp < 0)
		temp = (-b + sqrtf(discriminant)) / (2.0f * a);
	if (temp < 0)
		return (false);
	*t = temp;
	return (true);
}
