#include "color.h"

t_color	color_modul(t_color a, t_color b)
{
	t_color	rtn;

	rtn.r = (a.r * b.r) / 255;
	rtn.g = (a.g * b.g) / 255;
	rtn.b = (a.b * b.b) / 255;
	return (rtn);
}
