/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:26:26 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:26:27 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "render.h"
#include "entities.h"

bool	hit_sphere(t_sphere *s, t_ray r, float *t_hit)
{
	t_vec3	oc;
	float	radius;
	float	a;
	float	b;
	float	c;

	oc = vec_sub(r.origin, s->pos);
	radius = s->dia / 2.0f;
	a = vec_dot(r.direction, r.direction);
	b = 2.0f * vec_dot(oc, r.direction);
	c = vec_dot(oc, oc) - radius * radius;
	if (!solve_quadratic(a, b, c, t_hit))
		return (false);
	return (true);
}
