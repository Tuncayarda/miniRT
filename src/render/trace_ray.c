#include <math.h>
#include "util.h"
#include "entities.h"
#include "render.h"
#include "color.h"
#include "libft.h"

typedef struct	s_trace_var
{
	plane		*pl;
	sphere		*sp;
	cylinder	*cy;
	circle		*c;
	ent_type	type;
	material	mat;

	size_t		i;
	int		closest_i;
	float	t;
	float	closest_t;

	vec3	hit_p;
	vec3	normal;
	vec3	l_dir;
	color	base;

	color	diffuse;
	color	ambient;
	color	total_diffuse;
	size_t	li;
	float	diffuse_int;

	color	specular;
	color	total_specular;
}				trace_var;


bool	get_closest(scene *sc, trace_var	*var, ray r)
{
	var->i = 0;
	var->type = ENT_UNKNOWN;
	var->closest_i = -1;
	var->closest_t = INFINITY;
	while (var->i < sc->ent_count)
	{
		if ((sc->ents[var->i].type == ENT_SPHERE && hit_sphere(sc->ents[var->i].ent, r, &var->t) && var->t < var->closest_t)
			|| (sc->ents[var->i].type == ENT_CYLINDER && hit_cylinder(sc->ents[var->i].ent, r, &var->t) && var->t < var->closest_t)
			|| (sc->ents[var->i].type == ENT_CIRCLE && hit_circle(sc->ents[var->i].ent, r, &var->t) && var->t < var->closest_t)
			|| (sc->ents[var->i].type == ENT_PLANE && hit_plane(sc->ents[var->i].ent, r, &var->t) && var->t < var->closest_t))
		{
				var->closest_t = var->t;
				var->closest_i = var->i;
				var->type = sc->ents[var->i].type;
		}
		var->i++;
	}
	if (var->closest_i == -1)
		return (false);
	return (true);
}

void	define_closest(scene *sc, trace_var	*var, ray r)
{
	var->base = COLOR_INIT;
	var->normal = VECTOR_INIT;
	var->hit_p = vec_add(r.origin, vec_scale(r.direction, var->closest_t));
	if (var->type == ENT_SPHERE)
	{
		var->sp = (sphere *)sc->ents[var->closest_i].ent;
		var->normal = vec_norm(vec_sub(var->hit_p, var->sp->pos));
		var->base = var->sp->color;
		var->mat = var->sp->mat;
	}
	else if (var->type == ENT_PLANE)
	{
		var->pl = (plane *)sc->ents[var->closest_i].ent;
		var->normal = vec_norm(var->pl->axis);
		if (vec_dot(var->normal, vec_scale(r.direction, -1.0f)) < 0.0f)
			var->normal = vec_scale(var->normal, -1.0f);
		var->base = var->pl->color;
		var->mat = var->pl->mat;
	}
	else if (var->type == ENT_CYLINDER)
	{
		var->cy = (cylinder *)sc->ents[var->closest_i].ent;

		vec3 hp_rel = vec_sub(var->hit_p, var->cy->pos);
		float t0 = vec_dot(hp_rel, vec_norm(var->cy->axis));
		vec3 Q = vec_add(var->cy->pos, vec_scale(vec_norm(var->cy->axis), t0));

		vec3 to_axis = vec_sub(Q, var->hit_p);
		float s = vec_dot(to_axis, r.direction);
		bool hit_from_inside = (s < 0.0f);

		vec3 N_out = vec_norm(vec_sub(var->hit_p, Q));

		var->normal = N_out;
		if (!hit_from_inside)
			vec_scale(N_out, -1.0f);

		var->base = var->cy->color;
		var->mat = var->cy->mat;
	}
	else if (var->type == ENT_CIRCLE)
	{
		var->c = (circle *)sc->ents[var->closest_i].ent;
		var->normal = vec_norm(var->c->axis);
		if (vec_dot(var->normal, vec_scale(r.direction, -1.0f)) < 0.0f)
			var->normal = vec_scale(var->normal, -1.0f);
		var->base = var->c->color;
		var->mat = var->c->mat;
	}
}

void	compute_diffuse(scene *sc, trace_var	*var, ray r)
{
	(void)r;
	var->li = 0;
	var->total_diffuse = COLOR_INIT;
	var->ambient = color_scale(color_modul(var->base, sc->ambient.color), sc->ambient.ratio);
	while (var->li < sc->light_count)
	{
		var->l_dir = vec_norm(vec_sub(sc->lights[var->li].pos, var->hit_p));
		var->diffuse_int = fmaxf(0.0f, vec_dot(var->normal, var->l_dir)) * sc->lights[var->li].ratio;
		var->diffuse = color_scale(color_modul(var->base, sc->lights[var->li].color), var->diffuse_int);
		var->total_diffuse = color_add(var->total_diffuse, var->diffuse);
		var->li++;
	}
}

void	compute_specular(scene *sc, trace_var	*var, ray r)
{
	var->li = 0;
	var->specular = COLOR_INIT;
	var->total_specular = COLOR_INIT;
	if (var->mat.has_spc)
	{
		while (var->li < sc->light_count)
		{
			var->specular = COLOR_INIT;
			vec3	N = var->normal;
			vec3	L = vec_norm(vec_sub(sc->lights[var->li].pos, var->hit_p));
			vec3	V = vec_norm(vec_scale(r.direction, -1.0f));
			float	NL = vec_dot(N, L);
			vec3	R = vec_norm(vec_sub(vec_scale(N, 2.0f * NL), L));
			float	specular_int;
			float	spec_term;
			if (NL > 0)
			{
				spec_term = powf(fmax(0, vec_dot(R, V)), var->mat.shininess);
				specular_int = var->mat.specular_strength * spec_term * sc->lights[var->li].ratio;
				var->specular = color_scale(sc->lights[var->li].color, specular_int);
				var->total_specular = color_add(var->total_specular, var->specular);
			}
			var->li++;
		}	
	}
}

color	trace_ray(scene *sc, ray r)
{
	trace_var var;

	ft_memset(&var, 0, sizeof(trace_var));
	if (!get_closest(sc, &var, r))
		return (color_scale(sc->ambient.color, sc->ambient.ratio));
	define_closest(sc , &var, r);
	compute_diffuse(sc, &var, r);
	compute_specular(sc, &var, r);

	return (color_add(var.ambient, color_add(var.total_diffuse, var.total_specular)));
}
