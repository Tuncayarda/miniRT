#include <math.h>
#include "mlx_interface.h"
#include "vector.h"
#include "minirt.h"

static bool	handle_move(int key, scene *sc)
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

static bool	handle_vertical(int key, scene *sc)
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

static bool	handle_look(int key, scene *sc)
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

static bool	handle_fov(int key, scene *sc)
{
	if (key == KEY_K)
	{
		if (sc->cam.fov > 1)
			sc->cam.fov -= FOV_STEP_DEG;
		return (true);
	}
	else if (key == KEY_L)
	{
		if (sc->cam.fov < 179)
			sc->cam.fov += FOV_STEP_DEG;
		return (true);
	}
	return (false);
}

int	on_key(int key, void *param)
{
	scene	*sc;
	bool	changed;

	sc = (scene *)param;
	changed = false;
	if (handle_move(key, sc))
		changed = true;
	if (handle_vertical(key, sc))
		changed = true;
	if (handle_look(key, sc))
		changed = true;
	if (handle_fov(key, sc))
		changed = true;
	if (key == KEY_R)
	{
		reset_scene(sc);
		return (0);
	}
	if (key == KEY_ESC)
	{
		gc_manager(NULL, MODE_FREE);
		exit(0);
	}
	if (changed)
		recalc_camera(sc);
	return (0);
}
