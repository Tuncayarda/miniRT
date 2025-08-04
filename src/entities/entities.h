#ifndef __ENTITIES_H__
# define __ENTITIES_H__

# include <stdlib.h>
# include "vector.h"

typedef union		u_color
{
	struct
	{
		__uint8_t	b;
		__uint8_t	g;
		__uint8_t	r;
		__uint8_t	a;
	};
	__uint32_t		val;
}					color;

typedef enum	e_ent_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_UNKNOWN
}				ent_type;

typedef struct		s_entity
{
	ent_type		type;
	void			*ent;
}					entity;

typedef struct		s_ambient_light
{
	float			ratio;
	color			color;
}					ambient_light;

typedef struct		s_camera
{
	vec3			loc;
	vec3			dir;
	__uint8_t		fov;
}					camera;

typedef struct		s_light
{
	vec3			loc;
	color			color;
	float			ratio;
}					light;

typedef struct		s_sphere
{
	vec3			loc;
	color			color;
	float			dia;
}					sphere;

typedef struct		s_plane
{
	vec3			loc;
	vec3			axis;
	color			color;
}					plane;

typedef struct		s_cylinder
{
	vec3			loc;
	vec3			axis;
	color			color;
	float			dia;
	float			h;
}					cylinder;

typedef struct	s_scene scene;

void	add_light(scene *sc, vec3 loc, color color, float ratio);

#endif