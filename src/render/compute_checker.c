#include <math.h>
#include "render.h"

static t_color get_checker_cylinder(t_trace_var *var)
{
	if (fabsf(var->cy->axis.y) < 0.99f)
		var->ref_axis = vec_gen(0, 1, 0);
	else
		var->ref_axis = vec_gen(1, 0, 0);

	var->tan = vec_norm(vec_cross(var->ref_axis, var->cy->axis));
	var->bitan = vec_norm(vec_cross(var->cy->axis, var->tan));

	var->local = vec_sub(var->hit_p, var->cy->pos);

	var->v = vec_dot(var->local, var->cy->axis);
	var->radial = vec_sub(var->local, vec_scale(var->cy->axis, var->v));
	var->u = atan2f(vec_dot(var->radial, var->bitan), vec_dot(var->radial, var->tan)) / (2.0f * M_PI);

	if (var->cy->h > 0.0f)
        var->v = (var->v + 0.5f * var->cy->h) / var->cy->h;

	var->iu = (int)floorf(var->u * var->mat.checker_scale);
	var->iv = (int)floorf(var->v * var->mat.checker_scale);
	if (((var->iu + var->iv) & 1) == 0)
		return var->mat.checker_color;
	else
		return var->base;
}

static t_color get_checker_circle(t_trace_var *var)
{
	if (fabsf(var->normal.y) < 0.99f)
		var->ref_axis = vec_gen(0, 1, 0);
	else
		var->ref_axis = vec_gen(1, 0, 0);

	var->tan = vec_norm(vec_cross(var->ref_axis, var->normal));
	var->bitan = vec_norm(vec_cross(var->normal, var->tan));

	var->local = vec_sub(var->hit_p, var->c->pos);

	var->u = atan2f(vec_dot(var->local, var->bitan), vec_dot(var->local, var->tan)) / (2.0f * M_PI);

	var->iu = (int)floorf(var->u * var->mat.checker_scale);
	if ((var->iu & 1) == 0)
		return var->mat.checker_color;
	else
		return var->base;
}

static t_color get_checker_plane(t_trace_var *var)
{
	if (fabsf(var->normal.y) < 0.99f)
		var->ref_axis = vec_gen(0, 1, 0);
	else
		var->ref_axis = vec_gen(1, 0, 0);

	var->tan = vec_norm(vec_cross(var->ref_axis, var->normal));
	var->bitan = vec_norm(vec_cross(var->normal, var->tan));

	var->local = vec_sub(var->hit_p, var->pl->pos);

	var->u = vec_dot(var->local, var->tan);
	var->v = vec_dot(var->local, var->bitan);

	var->iu = (int)floorf(var->u * var->mat.checker_scale);
	var->iv = (int)floorf(var->v * var->mat.checker_scale);
	if (((var->iu + var->iv) & 1) == 0)
		return var->mat.checker_color;
	else
		return var->base;
}

static t_color get_checker_sphere(t_trace_var *var)
{
	var->local = vec_norm(vec_sub(var->hit_p, var->sp->pos));

	var->u = 0.5f + atan2f(var->local.z, var->local.x) / (2.0f * M_PI);
	var->v = 0.5f - asinf(var->local.y) / M_PI;

	var->iu = (int)floorf(var->u * var->mat.checker_scale);
	var->iv = (int)floorf(var->v * var->mat.checker_scale);

    if (((var->iu + var->iv) & 1) == 0)
        return var->mat.checker_color;
    else
        return var->base;
}
 
void	compute_checker(t_scene *sc, t_trace_var *var)
{
	(void)sc;

	if (var->mat.has_checker)
	{
		if (var->type == ENT_SPHERE)
			var->base = get_checker_sphere(var);
		else if (var->type == ENT_PLANE)
			var->base = get_checker_plane(var);
		else if (var->type == ENT_CYLINDER)
			var->base = get_checker_cylinder(var);
		else if (var->type == ENT_CIRCLE)
			var->base = get_checker_circle(var);
	}
}
