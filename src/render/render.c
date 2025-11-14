#include "render.h"

int	render(t_scene *sc)
{
	size_t	x;
	size_t	y;
	t_ray	r;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			r = generate_ray(&sc->cam, x, y);
			put_pix(&sc->mlx, x, y, trace_ray(sc, r));
			x++;
		}
		y++;
	}
	return (0);
}
