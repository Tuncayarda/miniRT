#ifndef __ENTITIES_H__
# define __ENTITIES_H__

# include <stdlib.h>
# include <stdbool.h>
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

typedef enum		e_ent_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_UNKNOWN
}					ent_type;

typedef struct s_material
{
	bool			has_spc;
	float			specular_strength;   // Intensity of specular reflection (spc:x)
	float			shininess;           // Shininess factor controlling specular spread (spc:y)

	bool			has_checker;
	color			checker_color;       // Base color used for checker pattern (if enabled)
	float			checker_scale;       // Scale of the checker pattern (pat:x)

	bool			has_texture;
	char			*texture_path;       // File path to texture map (txm)
	float			texture_scale;       // Scale/repetition factor for texture (txm:scale)
	void			*texture_img;        // Pointer to loaded texture image

	bool			has_bump;
	char			*bump_path;          // File path to bump map (bum)
	float			bump_strength;       // Strength/depth of bump effect (bum:scale)
	void			*bump_img;           // Pointer to loaded bump image
}					material;

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
	vec3			pos;
	vec3			dir;
	__uint8_t		fov;
}					camera;

typedef enum		e_light_type
{
	LIGHT_POINT,
	LIGHT_SPOT,
}					t_light_type;

typedef struct		s_light
{
	vec3			pos;
	color			color;
	float			ratio;
	t_light_type	type;
	vec3			dir;
	float			angle;
}					light;

typedef struct		s_sphere
{
	vec3			pos;
	color			color;
	float			dia;
	material		mat;
}					sphere;

typedef struct		s_plane
{
	vec3			pos;
	vec3			axis;
	color			color;
	material		mat;
}					plane;

typedef struct		s_cylinder
{
	vec3			pos;
	vec3			axis;
	color			color;
	float			dia;
	float			h;
	material		mat;
}					cylinder;

typedef struct	s_scene scene;

void	add_light(scene *sc, light l);

#endif