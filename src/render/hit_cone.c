/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 21:52:45 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 22:16:17 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "entities.h"
#include "vector.h"
#include "util.h"
#include "render.h"

bool	hit_cone(t_cone *co, t_ray r, float *t_hit)
{
	t_vec3	oc;
	float	radius;
	float	height;
	float	a;
	float	b;
	float	c;

	oc = vec_sub(r.origin, co->pos);
	a = (vec_dot(r.direction, co->axis) * vec_dot(r.direction, co->axis))
		- (cosf((co->angle / 2) * (M_PI / 180)) * cosf((co->angle / 2) * (M_PI / 180)));
	b = 2 * (vec_dot(r.direction, co->axis) * vec_dot(oc, co->axis) - vec_dot(r.direction, vec_scale(oc, cosf((co->angle / 2) * (M_PI / 180)))));
	c = vec_dot(oc, co->axis) * vec_dot(oc, co->axis) - vec_dot(oc, vec_scale(oc, cosf((co->angle / 2) * (M_PI / 180))));
	if (!solve_quadratic(a, b, c, t_hit))
		return (false);
	return (true);
}