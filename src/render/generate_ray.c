#include "render.h"

ray generate_ray(camera *cam, int x, int y)
{
	vec3	dir;
	ray		r;
	float	u;
	float	v;

	u = (2.0f * ((x + 0.5f) / WIDTH) - 1.0f) * cam->half_width;
	v = (1.0f - 2.0f * ((y + 0.5f) / HEIGHT)) * cam->half_height; 
	dir = vec_add3(
		vec_scale(cam->right, u),
		vec_scale(cam->up, v),
		cam->dir);
	r.origin = cam->pos;
	r.direction = vec_norm(dir);
	return (r);
}

