#include <math.h>
#include "minirt.h"
#include "parser.h"
#include "libft.h"
#include "render.h"
#include "mlx_interface.h"

#include <sys/time.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	t_scene sc;
	ft_memset(&sc, 0, sizeof(t_scene));
	init_mlx(&sc.mlx);
	sc.av = av;
	parser(&sc, ac, av);

	mlx_key_hook(sc.mlx.win, on_key, &sc);
	mlx_hook(sc.mlx.win, 2, (1L<<0), on_key, &sc);
	mlx_loop_hook(sc.mlx.ptr, render, &sc);
	mlx_loop(sc.mlx.ptr);
	gc_manager(NULL, MODE_FREE);
	return 0;
}
