#include <mlx.h>
#include "minirt.h"
#include "mlx_interface.h"

void	put_pix(mlx *m, size_t x, size_t y, color color)
{
	char	*pixel;

	if (x >= WIDTH || y >= HEIGHT)
		return ;
	pixel = m->addr + (y * m->line_len + x * (m->bpp / 8));
	pixel[0] = color.b;
	pixel[1] = color.g;
	pixel[2] = color.r;
	pixel[3] = color.a;
}
