#include "render.h"

void	render(scene *sc)
{
	#pragma omp parallel for schedule(dynamic, 4)
	size_t	x;
	size_t	y;
	ray		r;

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
}
