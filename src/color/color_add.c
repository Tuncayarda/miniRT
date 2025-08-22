#include <math.h>
#include "color.h"

t_color	color_add(t_color a, t_color b)
{
	t_color	rtn;

	rtn.r = fminf(255, a.r + b.r);
	rtn.g = fminf(255, a.g + b.g);
	rtn.b = fminf(255, a.b + b.b);
	return (rtn);
}
