#include <math.h>
#include "render.h"

static t_color get_texture_sphere(t_trace_var *var)
{
	var->local = vec_norm(vec_sub(var->hit_p, var->sp->pos));

	var->u = 0.5f + atan2f(var->local.z, var->local.x) / (2.0f * M_PI);
	var->u = 1.0f - var->u;
	var->v = 0.5f - asinf(var->local.y) / M_PI;

	var->iu = (int)floorf(var->u * (float)var->mat.tex_width);
	var->iv = (int)floorf(var->v * (float)var->mat.tex_height);

	int bpp_bytes = var->mat.tex_bpp / 8;
	const unsigned char *pix = (const unsigned char*)(var->mat.tex_addr + var->iv * var->mat.tex_line_len + var->iu * bpp_bytes);

	t_color c;
	c.b = pix[0];
	c.g = pix[1];
	c.r = pix[2];
	return c;
}

static t_color get_texture_plane(t_trace_var *var)
{
	
}

static t_color get_texture_cylinder(t_trace_var *var)
{
	
}

static t_color get_texture_circle(t_trace_var *var)
{
	
}

void	compute_texture(t_scene *sc, t_trace_var *var)
{
	(void)sc;

	if (var->mat.has_texture)
	{
		if (var->type == ENT_SPHERE)
			var->base = get_texture_sphere(var);
		else if (var->type == ENT_PLANE)
			var->base = get_texture_plane(var);
		else if (var->type == ENT_CYLINDER)
			var->base = get_texture_cylinder(var);
		else if (var->type == ENT_CIRCLE)
			var->base = get_texture_circle(var);
	}
}
