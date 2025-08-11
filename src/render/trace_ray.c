
#include <math.h>
#include "util.h"
#include "entities.h"
#include "render.h"
#include "color.h"

color	trace_ray(scene *sc, ray r)
{
	size_t	i;
	int		closest_i;
	float	t;
	float	closest_t;

	i = 0;
	closest_i = -1;
	closest_t = INFINITY;
	while (i < sc->ent_count)
	{
		if (sc->ents[i].type == ENT_SPHERE)
		{
			if (hit_sphere(sc->ents[i].ent, r, &t) && t < closest_t)
			{
				closest_t = t;
				closest_i = i;
			}
		}
		i++;
	}
	if (closest_i == -1)
		return (color_scale(sc->ambient.color, sc->ambient.ratio));

	vec3	hit_p;
	vec3	normal;
	vec3	l_dir;
	color	base;
	float	intensity;

	base = COLOR_INIT;
	normal = VECTOR_INIT;
	hit_p = vec_add(r.origin, vec_scale(r.direction, closest_t));
	if (sc->ents[closest_i].type == ENT_SPHERE)
	{
		normal = vec_norm(vec_sub(hit_p, ((sphere *)sc->ents[closest_i].ent)->pos));
		base = ((sphere *)sc->ents[closest_i].ent)->color;
	}

	l_dir = vec_norm(vec_sub(sc->lights[0].pos, hit_p));
	intensity = fmaxf(0.0f, vec_dot(normal, l_dir)) * sc->lights[0].ratio;

	color	diffuse;
	color	ambient;

	diffuse = color_scale(color_mod(base, sc->lights[0].color), intensity);
	ambient = color_scale(color_mod(base, sc->ambient.color), sc->ambient.ratio);

	return (color_add(ambient, diffuse));
}
