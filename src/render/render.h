#ifndef __RENDER_H__
# define __RENDER_H__

# include "vector.h"
# include "minirt.h"

# define EPSILON 1e-6f
# define SHADOW_BIAS 1e-3f

typedef struct	s_ray
{
	t_vec3		origin;
	t_vec3		direction;
}				ray;

typedef struct	s_trace_var
{
	t_plane		*pl;
	t_sphere	*sp;
	t_cylinder	*cy;
	t_circle	*c;
	t_ent_type	type;
	t_material	mat;

	size_t		i;
	int		closest_i;
	float	t;
	float	closest_t;

	t_vec3	hit_p;
	t_vec3	normal;
	t_vec3	l_dir;
	t_color	base;

	t_color	diffuse;
	t_color	ambient;
	t_color	total_diffuse;
	size_t	li;
	float	diffuse_int;

	t_color	specular;
	t_color	total_specular;
}				trace_var;

void	render(scene *sc);

ray 	generate_ray(t_camera *cam, int x, int y);
t_color	trace_ray(scene *sc, ray r);

bool	solve_quadratic(float a, float b, float c, float *t);

bool	hit_sphere(t_sphere *s, ray r, float *t_hit);
bool	hit_plane(t_plane *pl, ray r, float *t_hit);
bool	hit_cylinder(t_cylinder *cy, ray r, float *t_hit);
bool	hit_circle(t_circle *c, ray r, float *t_hit);

bool	check_hit(scene *sc, trace_var *var, ray r, size_t i);
bool	get_closest(scene *sc, trace_var *var, ray r);
void	define_closest(scene *sc, trace_var	*var, ray r);
void	compute_diffuse(scene *sc, trace_var *var);

#endif
