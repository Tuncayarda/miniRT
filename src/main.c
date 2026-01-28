/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:27:35 by tuaydin           #+#    #+#             */
/*   Updated: 2026/01/28 19:12:59 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "parser.h"
#include "libft.h"
#include "render.h"
#include "mlx_interface.h"
#include <sys/time.h>

static void	init_mlx(t_mlx *m)
{
	m->ptr = mlx_init();
	m->win = mlx_new_window(m->ptr, WIDTH, HEIGHT, "miniRT");
	m->img = mlx_new_image(m->ptr, WIDTH, HEIGHT);
	m->addr = mlx_get_data_addr(m->img, &m->bpp, &m->line_len, &m->endian);
}

int	main(int ac, char **av)
{
	t_scene	sc;

	ft_memset(&sc, 0, sizeof(t_scene));
	init_mlx(&sc.mlx);
	sc.av = av;
	parser(&sc, ac, av);
	mlx_key_hook(sc.mlx.win, on_key, &sc);
	mlx_hook(sc.mlx.win, 2, (1L << 0), on_key, &sc);
	mlx_hook(sc.mlx.win, 17, 0, destroy_prog, &sc);
	mlx_loop_hook(sc.mlx.ptr, render, &sc);
	mlx_loop(sc.mlx.ptr);
	gc_manager(NULL, MODE_FREE);
	return (0);
}
