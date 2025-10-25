#include <math.h>
#include "render.h"

static inline t_color sample_uv(t_trace_var *var)
{
	t_color				c;
	int					bpp_bytes;
	const unsigned char	*pix;

	var->iu = (int)floorf(var->u * (float)var->mat.tex_width);
	var->iv = (int)floorf(var->v * (float)var->mat.tex_height);
	if (var->iu < 0)
		var->iu = 0;
	if (var->iu >= var->mat.tex_width) 
		var->iu = var->mat.tex_width  - 1;
	if (var->iv < 0)
		var->iv = 0;
	if (var->iv >= var->mat.tex_height)
		var->iv = var->mat.tex_height - 1;
	bpp_bytes = var->mat.tex_bpp / 8;
	pix = (const unsigned char*)(var->mat.tex_addr + var->iv * var->mat.tex_line_len + var->iu * bpp_bytes);
	c.b = pix[0];
	c.g = pix[1];
	c.r = pix[2];
	return (c);
}

static t_color get_texture_sphere(t_trace_var *var)
{
	var->local = vec_norm(vec_sub(var->hit_p, var->sp->pos));
	var->u = 0.5f + atan2f(var->local.z, var->local.x) / (2.0f * M_PI);
	if (var->u < 0.0f) var->u += 1.0f;
	var->u = 1.0f - var->u;     
	var->v = 0.5f - asinf(var->local.y) / M_PI;
	
	return (sample_uv(var));
}

static t_color get_texture_plane(t_trace_var *var)
{
	if (fabsf(var->normal.y) < 0.99f)
		var->ref_axis = vec_gen(0, 1, 0);
	else
		var->ref_axis = vec_gen(1, 0, 0);
	var->tan = vec_norm(vec_cross(var->ref_axis, var->normal));
	var->bitan = vec_norm(vec_cross(var->normal, var->tan));
	var->local = vec_sub(var->hit_p, var->pl->pos);
	var->u = vec_dot(var->local, var->tan);
	var->v = vec_dot(var->local, var->bitan);

	return (sample_uv(var));
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
