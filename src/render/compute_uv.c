/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_uv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:25:33 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:40:26 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <math.h>
#include "render.h"

static void	compute_uv_cylinder(t_trace_var *var)
{
	if (fabsf(var->cy->axis.y) < 0.99f)
		var->ref_axis = vec_gen(0, 1, 0);
	else
		var->ref_axis = vec_gen(1, 0, 0);
	var->tan = vec_norm(vec_cross(var->ref_axis, var->cy->axis));
	var->bitan = vec_norm(vec_cross(var->cy->axis, var->tan));
	var->local = vec_sub(var->hit_p, var->cy->pos);
	var->v = -vec_dot(var->local, var->cy->axis);
	var->radial = vec_sub(var->local, vec_scale(var->cy->axis, var->v));
	var->u = 0.5f + atan2f(vec_dot(var->radial, var->bitan),
			vec_dot(var->radial, var->tan)) / (2.0f * M_PI);
	if (var->cy->h > 0.0f)
		var->v = (var->v + 0.5f * var->cy->h) / var->cy->h;
}

static void	compute_uv_circle(t_trace_var *var)
{
	if (fabsf(var->normal.y) < 0.99f)
		var->ref_axis = vec_gen(0, 1, 0);
	else
		var->ref_axis = vec_gen(1, 0, 0);
	var->tan = vec_norm(vec_cross(var->ref_axis, var->normal));
	var->bitan = vec_norm(vec_cross(var->normal, var->tan));
	var->local = vec_sub(var->hit_p, var->c->pos);
	var->u = atan2f(vec_dot(var->local, var->bitan),
			vec_dot(var->local, var->tan)) / (2.0f * M_PI);
	var->v = vec_dot(var->local, var->bitan);
}

static void	compute_uv_plane(t_trace_var *var)
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
}

static void	compute_uv_sphere(t_trace_var *var)
{
	var->local = vec_norm(vec_sub(var->hit_p, var->sp->pos));
	var->u = 0.5f + atan2f(var->local.z, var->local.x) / (2.0f * M_PI);
	if (var->u < 0.0f)
		var->u += 1.0f;
	var->u = 1.0f - var->u;
	var->v = 0.5f - asinf(var->local.y) / M_PI;
}

void	compute_uv(t_scene *sc, t_trace_var *var)
{
	(void)sc;
	if (var->type == ENT_SPHERE)
		compute_uv_sphere(var);
	else if (var->type == ENT_PLANE)
		compute_uv_plane(var);
	else if (var->type == ENT_CYLINDER)
		compute_uv_cylinder(var);
	else if (var->type == ENT_CIRCLE)
		compute_uv_circle(var);
}
