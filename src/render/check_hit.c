#include "render.h"

bool	check_hit(t_scene *sc, t_trace_var *var, t_ray r, size_t i)
{
	if ((sc->ents[i].type == ENT_SPHERE
			&& hit_sphere(sc->ents[i].ent, r, &var->t)
			&& var->t < var->closest_t)
		|| (sc->ents[i].type == ENT_CYLINDER
			&& hit_cylinder(sc->ents[i].ent, r, &var->t)
			&& var->t < var->closest_t)
		|| (sc->ents[i].type == ENT_CIRCLE
			&& hit_circle(sc->ents[i].ent, r, &var->t)
			&& var->t < var->closest_t)
		|| (sc->ents[i].type == ENT_PLANE
			&& hit_plane(sc->ents[i].ent, r, &var->t)
			&& var->t < var->closest_t))
	{
		return (true);
	}
	return (false);
}
