/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:25:30 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:43:24 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "render.h"

static inline void	fractf(float *x)
{
	*x = *x - floorf(*x);
}

static t_color	get_texture_color(t_trace_var *var)
{
	t_color				c;
	int					bpp_bytes;
	const unsigned char	*pix;

	fractf(&var->u);
	fractf(&var->v);
	var->iu = (int)floorf(var->u * (float)var->mat.tex_width);
	var->iv = (int)floorf(var->v * (float)var->mat.tex_height);
	if (var->iu < 0)
		var->iu = 0;
	if (var->iu >= var->mat.tex_width)
		var->iu = var->mat.tex_width - 1;
	if (var->iv < 0)
		var->iv = 0;
	if (var->iv >= var->mat.tex_height)
		var->iv = var->mat.tex_height - 1;
	bpp_bytes = var->mat.tex_bpp / 8;
	pix = (const unsigned char *)(var->mat.tex_addr + var->iv
			* var->mat.tex_line_len + var->iu * bpp_bytes);
	c.b = pix[0];
	c.g = pix[1];
	c.r = pix[2];
	return (c);
}

void	compute_texture(t_scene *sc, t_trace_var *var)
{
	(void)sc;
	if (var->mat.has_texture)
	{
		compute_uv(sc, var);
		var->base = get_texture_color(var);
	}
}
