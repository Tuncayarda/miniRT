/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_skybox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:26:48 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:36:28 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <math.h>

t_color	sample_skybox(t_scene *sc, t_ray ray)
{
	t_skybox_var	var;

	var.d = vec_norm(ray.direction);
	var.u = 0.5f + atan2f(var.d.z, var.d.x) / (2.0f * M_PI);
	var.v = 0.5f - asinf(var.d.y) / M_PI;
	if (var.u < 0.0f)
		var.u = 1.0f;
	if (var.u > 1.0f)
		var.u = 1.0f;
	if (var.v < 0.0f)
		var.v = 0.0f;
	if (var.v > 1.0f)
		var.v = 1.0f;
	var.iu = (int)(var.u * sc->sky.tex_width);
	var.iv = (int)(var.v * sc->sky.tex_height);
	var.pix = (const unsigned char *)(sc->sky.tex_addr + var.iv
			* sc->sky.tex_line_len + var.iu * (sc->sky.tex_bpp / 8));
	var.ret.b = var.pix[0];
	var.ret.g = var.pix[1];
	var.ret.r = var.pix[2];
	return (var.ret);
}
