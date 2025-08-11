#include <math.h>
#include "color.h"

color	color_add(color a, color b)
{
	color	rtn;

	rtn.r = fminf(255, a.r + b.r);
	rtn.g = fminf(255, a.g + b.g);
	rtn.b = fminf(255, a.b + b.b);
	return (rtn);
}
