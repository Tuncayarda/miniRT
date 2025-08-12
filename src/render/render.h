#ifndef __RENDER_H__
# define __RENDER_H__

# include "vector.h"
# include "minirt.h"

typedef struct	s_ray
{
	vec3		origin;
	vec3		direction;
}				ray;

void	render(scene *sc);

ray 	generate_ray(camera *cam, int x, int y);
color	trace_ray(scene *sc, ray r);

bool	hit_sphere(sphere *s, ray r, float *t_hit);
bool	hit_plane(plane *pl, ray r, float *t_hit);

#endif
