#include <math.h>
#include <string.h>
#include "mlx_interface.h"
#include "vector.h"
#include "minirt.h"
#include "libft.h"
#include "parser.h"

t_vec3	rotate_around_axis(t_vec3 v, t_vec3 axis, float angle_rad)
{
	t_vec3	k;
	float	c;
	float	s;
	t_vec3	term1;
	t_vec3	term2;
	t_vec3	term3;

	k = vec_norm(axis);
	c = cosf(angle_rad);
	s = sinf(angle_rad);
	term1 = vec_scale(v, c);
	term2 = vec_scale(vec_cross(k, v), s);
	term3 = vec_scale(k, vec_dot(k, v) * (1.0f - c));
	return (vec_add(vec_add(term1, term2), term3));
}

void	recalc_camera(scene *sc)
{
	float	fov_rad;
	t_vec3	up_hint;
	t_vec3	right;

	if (sc->cam.fov < 1)
		sc->cam.fov = 1;
	if (sc->cam.fov > 170)
		sc->cam.fov = 170;
	fov_rad = (float)sc->cam.fov * (M_PI / 180.0f);
	sc->cam.dir = vec_norm(sc->cam.dir);
	up_hint = vec_gen(0, 1, 0);
	right = vec_cross(sc->cam.dir, up_hint);
	if (fabsf(right.x) + fabsf(right.y) + fabsf(right.z) < 1e-6f)
	{
		up_hint = vec_gen(0, 0, 1);
		right = vec_cross(sc->cam.dir, up_hint);
	}
	sc->cam.right = vec_norm(right);
	sc->cam.up = vec_norm(vec_cross(sc->cam.right, sc->cam.dir));
	sc->cam.half_height = tanf(fov_rad * 0.5f);
	sc->cam.half_width = sc->cam.half_height * ASPECT_RATIO;
}

void reset_scene(t_scene *sc)
{
	gc_manager(NULL, MODE_FREE);
	sc->lights = NULL;
	sc->ents = NULL;
	sc->light_count = 0;
	sc->ent_count = 0;
	if (!sc->av || !sc->av[1])
		return ;
	parser(sc, 2, sc->av);
	recalc_camera(sc);
}
