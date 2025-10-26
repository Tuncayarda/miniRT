#include "render.h"
#include <math.h>

t_color sample_skybox(t_scene *sc, t_ray ray)
{
	t_vec3 d = vec_norm(ray.direction);

	float u = 0.5f + atan2f(d.z, d.x) / (2.0f * M_PI);
	float v = 0.5f - asinf(d.y) / M_PI;

	if (u < 0.0f) u += 1.0f;
	if (u > 1.0f) u -= 1.0f;
	if (v < 0.0f) v = 0.0f;
	if (v > 1.0f) v = 1.0f;

	int iu = (int)(u * sc->sky.tex_width);
	int iv = (int)(v * sc->sky.tex_height);

	const unsigned char *pix = (const unsigned char *)(sc->sky.tex_addr + iv * sc->sky.tex_line_len + iu * (sc->sky.tex_bpp / 8));

	t_color c;
	c.b = pix[0];
	c.g = pix[1];
	c.r = pix[2];
	return c;
}
