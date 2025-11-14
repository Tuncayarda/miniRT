/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_diffuse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:24:45 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:24:46 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "render.h"

void	compute_diffuse(t_scene *sc, t_trace_var *var)
{
	size_t	i;

	i = 0;
	var->ambient = color_scale(color_modul(var->base, sc->ambient.color),
			sc->ambient.ratio);
	while (i < sc->light_count)
	{
		if (is_reachable(sc, var, i))
		{
			var->diffuse_int = fmaxf(0.0f, vec_dot(var->normal, var->l_dir))
				* sc->lights[i].ratio;
			var->diffuse = color_scale(color_modul(var->base,
						sc->lights[i].color), var->diffuse_int);
			var->total_diffuse = color_add(var->total_diffuse, var->diffuse);
		}
		i++;
	}
}
