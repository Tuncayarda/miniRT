#include "color.h"

color	color_modul(color a, color b)
{
	color	rtn;

	rtn.r = (a.r * b.r) / 255;
	rtn.g = (a.g * b.g) / 255;
	rtn.b = (a.b * b.b) / 255;
	return (rtn);
}
