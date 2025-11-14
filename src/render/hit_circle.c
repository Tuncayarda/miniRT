/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_circle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:25:45 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:38:58 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "entities.h"
#include "vector.h"
#include "util.h"
#include "render.h"

bool	hit_circle(t_circle *c, t_ray r, float *t_hit)
{
	t_vec3	n;
	float	denom;
	float	t;
	t_vec3	p;
	t_vec3	v;

	n = vec_norm(c->axis);
	denom = vec_dot(n, r.direction);
	if (fabs(denom) < EPSILON)
		return (false);
	t = vec_dot(vec_sub(c->pos, r.origin), n) / denom;
	if (t <= (float)1e-4)
		return (false);
	*t_hit = t;
	p = vec_add(r.origin, vec_scale(r.direction, t));
	v = vec_sub(p, c->pos);
	if (vec_length(v) > c->radius)
		return (false);
	return (true);
}
