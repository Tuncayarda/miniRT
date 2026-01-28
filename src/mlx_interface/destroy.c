/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:09:03 by tuaydin           #+#    #+#             */
/*   Updated: 2026/01/28 19:17:20 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_interface.h"
#include "vector.h"
#include "minirt.h"

int	destroy_prog(void *param)
{
	t_scene	*sc;

	if (param)
	{
		sc = (t_scene *)param;
		gc_manager(NULL, MODE_FREE);
		mlx_destroy_image(sc->mlx.ptr, sc->mlx.img);
		mlx_destroy_window(sc->mlx.ptr, sc->mlx.win);
		mlx_destroy_display(sc->mlx.ptr);
		free(sc->mlx.ptr);
		exit(0);
	}
	return (0);
}
