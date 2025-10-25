#ifndef RENDER_H
# define RENDER_H

# include "vector.h"
# include "minirt.h"

# define EPSILON 1e-6f
# define SHADOW_BIAS 1e-3f

typedef struct s_ray
{
	t_vec3		origin;
	t_vec3		direction;
}				t_ray;

typedef struct s_spc_var
{
	t_vec3	n;
	t_vec3	l;
	t_vec3	v;
	t_vec3	r;
	float	nl;
	float	spc_int;
	float	spc_term;
}				t_spc_var;

typedef struct s_trace_var
{
	t_plane		*pl;
	t_sphere	*sp;
	t_cylinder	*cy;
	t_circle	*c;
	t_ent_type	type;
	t_material	mat;

	size_t		i;
	int			closest_i;
	float		t;
	float		closest_t;

	t_vec3		hit_p;
	t_vec3		normal;
	t_vec3		l_dir;
	t_color		base;

	t_color		diffuse;
	t_color		ambient;
	t_color		total_diffuse;
	size_t		li;
	float		diffuse_int;

	t_color		specular;
	t_color		total_specular;
	t_spc_var	spc;

	t_vec3		local;
	t_vec3		ref_axis;
	t_vec3		tan;
	t_vec3		bitan;
	t_vec3		radial;
	float		u;
	float		v;
	int			iu;
	int			iv;
}				t_trace_var;

void	render(scene *sc);

t_ray	generate_ray(t_camera *cam, int x, int y);
t_color	trace_ray(scene *sc, t_ray r);

bool	solve_quadratic(float a, float b, float c, float *t);

bool	hit_sphere(t_sphere *s, t_ray r, float *t_hit);
bool	hit_plane(t_plane *pl, t_ray r, float *t_hit);
bool	hit_cylinder(t_cylinder *cy, t_ray r, float *t_hit);
bool	hit_circle(t_circle *c, t_ray r, float *t_hit);

bool	check_hit(scene *sc, t_trace_var *var, t_ray r, size_t i);
bool	get_closest(scene *sc, t_trace_var *var, t_ray r);
void	define_closest(scene *sc, t_trace_var	*var, t_ray r);
void	compute_diffuse(scene *sc, t_trace_var *var);
void	compute_specular(t_scene *sc, t_trace_var *var, t_ray r);
void	compute_checker(t_scene *sc, t_trace_var *var);
void	compute_texture(t_scene *sc, t_trace_var *var);

#endif
