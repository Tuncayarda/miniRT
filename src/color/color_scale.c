#include "color.h"

color	color_scale(color clr, float intensity)
{
	color	rtn;

	rtn.r = clr.r * intensity;
	rtn.g = clr.g * intensity;
	rtn.b = clr.b * intensity;
	return (rtn);
}
