/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:25:40 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:25:41 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_ray	generate_ray(t_camera *cam, int x, int y)
{
	t_vec3	dir;
	t_ray	r;
	float	u;
	float	v;

	u = (2.0f * ((x + 0.5f) / WIDTH) - 1.0f) * cam->half_width;
	v = (1.0f - 2.0f * ((y + 0.5f) / HEIGHT)) * cam->half_height;
	dir = vec_add3(
			vec_scale(cam->right, u),
			vec_scale(cam->up, v),
			cam->dir);
	r.origin = cam->pos;
	r.direction = vec_norm(dir);
	return (r);
}
