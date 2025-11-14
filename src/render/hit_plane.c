/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:25:50 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:38:46 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "entities.h"
#include "vector.h"
#include "util.h"
#include "render.h"

bool	hit_plane(t_plane *pl, t_ray r, float *t_hit)
{
	t_vec3	n;
	float	denom;
	float	t;

	n = vec_norm(pl->axis);
	denom = vec_dot(n, r.direction);
	if (fabs(denom) < (float)1e-6)
		return (false);
	t = vec_dot(vec_sub(pl->pos, r.origin), n) / denom;
	if (t <= (float)1e-4)
		return (false);
	*t_hit = t;
	return (true);
}
