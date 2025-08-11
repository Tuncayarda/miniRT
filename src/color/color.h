#ifndef __COLOR_H__
# define __COLOR_H__

# include <stdint.h>

# define COLOR_INIT (color){{0, 0, 0}}

typedef union		u_color
{
	struct
	{
		__uint8_t	b;
		__uint8_t	g;
		__uint8_t	r;
	};
	__uint32_t		val;
}					color;

color	color_add(color a, color b);
color	color_mod(color a, color b);
color	color_scale(color clr, float intensity);
#endif