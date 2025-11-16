/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:24:39 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 21:54:25 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			&& var->t < var->closest_t)
		|| (sc->ents[i].type == ENT_CONE
			&& hit_cone(sc->ents[i].ent, r, &var->t)
			&& var->t < var->closest_t))
		return (true);
	return (false);
}
