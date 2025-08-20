#ifndef __RENDER_H__
# define __RENDER_H__

# include "vector.h"
# include "minirt.h"

# define EPSILON 1e-6f

typedef struct	s_ray
{
	vec3		origin;
	vec3		direction;
}				ray;

void	render(scene *sc);

ray 	generate_ray(camera *cam, int x, int y);
color	trace_ray(scene *sc, ray r);

bool	solve_quadratic(float a, float b, float c, float *t);

bool	hit_sphere(sphere *s, ray r, float *t_hit);
bool	hit_plane(plane *pl, ray r, float *t_hit);
bool	hit_cylinder(cylinder *cy, ray r, float *t_hit);
bool	hit_circle(circle *c, ray r, float *t_hit);
#endif
