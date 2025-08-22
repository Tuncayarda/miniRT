#include "color.h"

t_color	color_scale(t_color clr, float intensity)
{
	t_color	rtn;

	rtn.r = clr.r * intensity;
	rtn.g = clr.g * intensity;
	rtn.b = clr.b * intensity;
	return (rtn);
}
