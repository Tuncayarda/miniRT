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
		if ((sc->ents[i].type == ENT_SPHERE && hit_sphere(sc->ents[i].ent, r, &t) && t < closest_t)
			|| (sc->ents[i].type == ENT_PLANE && hit_plane(sc->ents[i].ent, r, &t) && t < closest_t)
			|| (sc->ents[i].type == ENT_CYLINDER && hit_cylinder(sc->ents[i].ent, r, &t) && t < closest_t))
		{
				closest_t = t;
				closest_i = i;
		}
		i++;
	}
	if (closest_i == -1)
		return (color_scale(sc->ambient.color, sc->ambient.ratio));

	vec3	hit_p;
	vec3	normal;
	vec3	l_dir;
	color	base;

	base = COLOR_INIT;
	normal = VECTOR_INIT;
	hit_p = vec_add(r.origin, vec_scale(r.direction, closest_t));
	if (sc->ents[closest_i].type == ENT_SPHERE)
	{
		normal = vec_norm(vec_sub(hit_p, ((sphere *)sc->ents[closest_i].ent)->pos));
		base = ((sphere *)sc->ents[closest_i].ent)->color;
	}
	else if (sc->ents[closest_i].type == ENT_PLANE)
	{
		normal = vec_norm(((plane *)sc->ents[closest_i].ent)->axis);
		base = ((plane *)sc->ents[closest_i].ent)->color;
	}

	color	diffuse;
	color	ambient;
	color	total_diffuse;
	size_t	li;
	float	diffuse_int;

	li = 0;
	total_diffuse = COLOR_INIT;
	ambient = color_scale(color_modul(base, sc->ambient.color), sc->ambient.ratio);
	while (li < sc->light_count)
	{
		l_dir = vec_norm(vec_sub(sc->lights[li].pos, hit_p));
		diffuse_int = fmaxf(0.0f, vec_dot(normal, l_dir)) * sc->lights[li].ratio;
		diffuse = color_scale(color_modul(base, sc->lights[li].color), diffuse_int);
		total_diffuse = color_add(total_diffuse, diffuse);
		li++;
	}


	li = 0;
	color	specular;
	color	total_specular = COLOR_INIT;
	
	while (li < sc->light_count)
	{
		specular = COLOR_INIT;
		vec3	N = normal;
		vec3	L = vec_norm(vec_sub(sc->lights[li].pos, hit_p));
		vec3	V = vec_norm(vec_scale(r.direction, -1.0f));
		float	NL = vec_dot(N, L);
		vec3	R = vec_norm(vec_sub(vec_scale(N, 2.0f * NL), L));
		float	specular_int;
		float	spec_term;
		if (NL > 0 && sc->ents[closest_i].type == ENT_SPHERE)
		{
			spec_term = powf(fmax(0, vec_dot(R, V)), ((sphere *)sc->ents[closest_i].ent)->mat.shininess);
			specular_int = ((sphere *)sc->ents[closest_i].ent)->mat.specular_strength * spec_term * sc->lights[li].ratio;
			specular = color_scale(sc->lights[li].color, specular_int);
			total_specular = color_add(total_specular, specular);
		}
		else  if (NL > 0 && sc->ents[closest_i].type == ENT_PLANE)
		{
			spec_term = powf(fmax(0, vec_dot(R, V)), ((plane *)sc->ents[closest_i].ent)->mat.shininess);
			specular_int = ((plane *)sc->ents[closest_i].ent)->mat.specular_strength * spec_term * sc->lights[li].ratio;
			specular = color_scale(sc->lights[li].color, specular_int);
			total_specular = color_add(total_specular, specular);
		}
		li++;
	}

	return (color_add(ambient, color_add(total_diffuse, total_specular)));
}
