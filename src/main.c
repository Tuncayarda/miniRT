#include <math.h>
#include "minirt.h"
#include "parser.h"
#include "libft.h"
#include "render.h"
#include "mlx_interface.h"
#include "debug.h"

#include <sys/time.h>
#include <stdio.h>

static void	init_mlx(mlx *m)
{
	m->ptr  = mlx_init();
	m->win  = mlx_new_window(m->ptr, WIDTH, HEIGHT, "miniRT");
	m->img  = mlx_new_image(m->ptr, WIDTH, HEIGHT);
	m->addr = mlx_get_data_addr(m->img, &m->bpp, &m->line_len, &m->endian);
}

static int	render_loop(void *param)
{
	scene *sc = (scene *)param;
	static struct timeval tv_last;
	static char frame_time_text[64] = "Frame: -- ms";
	static int initialized = 0;

	if (!initialized)
	{
		gettimeofday(&tv_last, NULL);
		initialized = 1;
	}

	render(sc);
	mlx_put_image_to_window(sc->mlx.ptr, sc->mlx.win, sc->mlx.img, 0, 0);

	struct timeval tv_now;
	gettimeofday(&tv_now, NULL);
	double elapsed_ms = (tv_now.tv_sec - tv_last.tv_sec) * 1000.0 + (tv_now.tv_usec - tv_last.tv_usec) / 1000.0;
	snprintf(frame_time_text, sizeof(frame_time_text), "Frame: %.2f ms", elapsed_ms);
	tv_last = tv_now;

	mlx_string_put(sc->mlx.ptr, sc->mlx.win, 10, 20, 0xFFFFFF, frame_time_text);
	return 0;
}

int	main(int ac, char **av)
{
	t_scene sc;
	ft_memset(&sc, 0, sizeof(t_scene));
	init_mlx(&sc.mlx);
	sc.av = av;
	parser(&sc, ac, av);
	print_scene_debug(&sc);

	mlx_key_hook(sc.mlx.win, on_key, &sc);
	mlx_hook(sc.mlx.win, 2, (1L<<0), on_key, &sc);
	mlx_loop_hook(sc.mlx.ptr, render_loop, &sc);
	mlx_loop(sc.mlx.ptr);
	gc_manager(NULL, MODE_FREE);
	return 0;
}
