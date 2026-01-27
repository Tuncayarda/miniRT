/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_reacheable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:26:29 by tuaydin           #+#    #+#             */
/*   Updated: 2026/01/27 23:12:33 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "render.h"

static bool	is_blocked(t_scene *sc, t_ray sray, float l_dist, size_t ignore_i)
{
	size_t	i;
	float	t;

	i = 0;
	while (i < sc->ent_count)
	{
		if (i == ignore_i)
		{
			i++;
			continue ;
		}
		if (((sc->ents[i].type == ENT_SPHERE
					&& hit_sphere(sc->ents[i].ent, sray, &t))
				|| (sc->ents[i].type == ENT_CYLINDER
					&& hit_cylinder(sc->ents[i].ent, sray, &t))
				|| (sc->ents[i].type == ENT_CIRCLE
					&& hit_circle(sc->ents[i].ent, sray, &t))
				|| (sc->ents[i].type == ENT_PLANE
					&& hit_plane(sc->ents[i].ent, sray, &t)))
			&& (t > SHADOW_BIAS && t < l_dist))
			return (true);
		i++;
	}
	return (false);
}

bool	is_reachable(t_scene *sc, t_trace_var *var, size_t i)
{
	t_vec3	to_light;
	float	l_dist;
	t_ray	sray;

	to_light = vec_sub(sc->lights[i].pos, var->hit_p);
	l_dist = vec_length(to_light);
	var->l_dir = vec_norm(vec_sub(sc->lights[i].pos, var->hit_p));
	sray.origin = var->hit_p;
	sray.direction = var->l_dir;
	if (is_blocked(sc, sray, l_dist, var->closest_i))
		return (false);
	return (true);
}
