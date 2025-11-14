/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:26:54 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:28:10 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "util.h"
#include "entities.h"
#include "render.h"
#include "color.h"
#include "libft.h"

t_color	trace_ray(t_scene *sc, t_ray r)
{
	t_trace_var	var;

	ft_bzero(&var.total_diffuse, sizeof(t_color));
	ft_bzero(&var.total_specular, sizeof(t_color));
	if (!get_closest(sc, &var, r))
	{
		if (sc->sky.has_skybox)
			return (sample_skybox(sc, r));
		else
			return (color_scale(sc->ambient.color, sc->ambient.ratio));
	}
	define_closest(sc, &var, r);
	compute_texture(sc, &var);
	compute_checker(sc, &var);
	compute_diffuse(sc, &var);
	if (var.mat.has_spc)
		compute_specular(sc, &var, r);
	return (color_add(var.ambient,
			color_add(var.total_diffuse, var.total_specular)));
}
