/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:26:44 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:26:45 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	mlx_put_image_to_window(sc->mlx.ptr, sc->mlx.win, sc->mlx.img, 0, 0);
	return (0);
}
