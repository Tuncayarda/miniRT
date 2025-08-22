#include "render.h"

static void	define_sphere(t_scene *sc, trace_var *var)
{
	var->sp = (t_sphere *)sc->ents[var->closest_i].ent;
	var->normal = vec_norm(vec_sub(var->hit_p, var->sp->pos));
	var->base = var->sp->color;
	var->mat = var->sp->mat;
}

static void	define_plane(t_scene *sc, trace_var *var, ray r)
{
	var->pl = (t_plane *)sc->ents[var->closest_i].ent;
	var->normal = vec_norm(var->pl->axis);
	if (vec_dot(var->normal, vec_scale(r.direction, -1.0f)) < 0.0f)
		var->normal = vec_scale(var->normal, -1.0f);
	var->base = var->pl->color;
	var->mat = var->pl->mat;
}

static void	define_cylinder(t_scene *sc, trace_var *var, ray r)
{
	t_vec3	q;
	t_vec3	normal;
	float	t;
	bool	hit_from_inside;

	var->cy = (t_cylinder *)sc->ents[var->closest_i].ent;
	t = vec_dot(vec_sub(var->hit_p, var->cy->pos), vec_norm(var->cy->axis));
	q = vec_add(var->cy->pos, vec_scale(vec_norm(var->cy->axis), t));
	hit_from_inside = (vec_dot(vec_sub(q, var->hit_p), r.direction) < 0.0f);
	normal = vec_norm(vec_sub(var->hit_p, q));
	var->normal = normal;
	if (!hit_from_inside)
		vec_scale(normal, -1.0f);
	var->base = var->cy->color;
	var->mat = var->cy->mat;
}

static void	define_circle(t_scene *sc, trace_var *var, ray r)
{
	var->c = (t_circle *)sc->ents[var->closest_i].ent;
	var->normal = vec_norm(var->c->axis);
	if (vec_dot(var->normal, vec_scale(r.direction, -1.0f)) < 0.0f)
		var->normal = vec_scale(var->normal, -1.0f);
	var->base = var->c->color;
	var->mat = var->c->mat;
}

void	define_closest(t_scene *sc, trace_var	*var, ray r)
{
	var->hit_p = vec_add(r.origin, vec_scale(r.direction, var->closest_t));
	if (var->type == ENT_SPHERE)
		define_sphere(sc, var);
	else if (var->type == ENT_PLANE)
		define_plane(sc, var, r);
	else if (var->type == ENT_CYLINDER)
		define_cylinder(sc, var, r);
	else if (var->type == ENT_CIRCLE)
		define_circle(sc, var, r);
}
