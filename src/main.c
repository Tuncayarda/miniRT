#include <math.h>
#include "minirt.h"
#include "parser.h"
#include "libft.h"
#include "render.h"
#include "mlx_interface.h"
#include "debug.h"

static void init_mlx(mlx *m)
{
    m->ptr  = mlx_init();
    m->win  = mlx_new_window(m->ptr, WIDTH, HEIGHT, "miniRT");
    m->img  = mlx_new_image(m->ptr, WIDTH, HEIGHT);
    m->addr = mlx_get_data_addr(m->img, &m->bpp, &m->line_len, &m->endian);
}

int main(int ac, char **av)
{
    scene sc;
    ft_memset(&sc,0,sizeof(sc));
    init_mlx(&sc.mlx);
    parser(&sc, ac, av);
	print_scene_debug(&sc);

    render(&sc);
    mlx_put_image_to_window(sc.mlx.ptr, sc.mlx.win, sc.mlx.img, 0, 0);
    mlx_loop(sc.mlx.ptr);
    gc_manager(NULL, MODE_FREE);
    return 0;
}
