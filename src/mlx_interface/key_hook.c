/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:23:50 by tuaydin           #+#    #+#             */
/*   Updated: 2026/01/28 19:12:32 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx_interface.h"
#include "vector.h"
#include "minirt.h"

static bool	handle_move(int key, t_scene *sc)
{
	if (key == KEY_W)
	{
		sc->cam.pos = vec_add(sc->cam.pos,
				vec_scale(sc->cam.dir, MOVE_STEP));
		return (true);
	}
	else if (key == KEY_S)
	{
		sc->cam.pos = vec_add(sc->cam.pos,
				vec_scale(sc->cam.dir, -MOVE_STEP));
		return (true);
	}
	else if (key == KEY_A)
	{
		sc->cam.pos = vec_add(sc->cam.pos,
				vec_scale(sc->cam.right, -MOVE_STEP));
		return (true);
	}
	else if (key == KEY_D)
	{
		sc->cam.pos = vec_add(sc->cam.pos,
				vec_scale(sc->cam.right, MOVE_STEP));
		return (true);
	}
	return (false);
}

static bool	handle_vertical(int key, t_scene *sc)
{
	if (key == KEY_Z)
	{
		sc->cam.pos = vec_add(sc->cam.pos,
				vec_scale(sc->cam.up, -MOVE_STEP));
		return (true);
	}
	else if (key == KEY_X)
	{
		sc->cam.pos = vec_add(sc->cam.pos,
				vec_scale(sc->cam.up, MOVE_STEP));
		return (true);
	}
	return (false);
}

static bool	handle_look(int key, t_scene *sc)
{
	float	step;

	step = ANGLE_STEP_DEG * (M_PI / 180.0f);
	if (key == KEY_LEFT)
	{
		sc->cam.dir = rotate_around_axis(sc->cam.dir, sc->cam.up, step);
		return (true);
	}
	else if (key == KEY_RIGHT)
	{
		sc->cam.dir = rotate_around_axis(sc->cam.dir, sc->cam.up, -step);
		return (true);
	}
	else if (key == KEY_UP)
	{
		sc->cam.dir = rotate_around_axis(sc->cam.dir, sc->cam.right, step);
		return (true);
	}
	else if (key == KEY_DOWN)
	{
		sc->cam.dir = rotate_around_axis(sc->cam.dir,
				sc->cam.right, -step);
		return (true);
	}
	return (false);
}

static bool	handle_fov(int key, t_scene *sc)
{
	if (key == KEY_K)
	{
		if (sc->cam.fov > 1)
			sc->cam.fov -= FOV_STEP_DEG;
		return (true);
	}
	else if (key == KEY_L)
	{
		if (sc->cam.fov < 174)
			sc->cam.fov += FOV_STEP_DEG;
		return (true);
	}
	return (false);
}

int	on_key(int key, void *param)
{
	t_scene	*sc;

	sc = (t_scene *)param;
	if (handle_move(key, sc))
		recalc_camera(sc);
	if (handle_vertical(key, sc))
		recalc_camera(sc);
	if (handle_look(key, sc))
		recalc_camera(sc);
	if (handle_fov(key, sc))
		recalc_camera(sc);
	if (key == KEY_R)
	{
		reset_scene(sc);
		return (0);
	}
	if (key == KEY_ESC)
		destroy_prog(param);
	return (0);
}
