#ifndef __ENTITIES_H__
# define __ENTITIES_H__

# include <stdlib.h>
# include <stdbool.h>
# include "vector.h"
# include "color.h"


typedef enum		e_ent_type
{
	ENT_SPHERE,
	ENT_PLANE,
	ENT_CYLINDER,
	ENT_UNKNOWN
}					ent_type;

typedef struct s_material
{
	bool			has_spc;
	bool			has_checker;
	bool			has_texture;
	bool			has_bump;

	float			specular_strength;   // Intensity of specular reflection (spc:x)
	float			shininess;           // Shininess factor controlling specular spread (spc:y)

	color			checker_color;       // Base color used for checker pattern (if enabled)
	float			checker_scale;       // Scale of the checker pattern (pat:x)

	float			texture_scale;       // Scale/repetition factor for texture (txm:scale)
	float			bump_strength;       // Strength/depth of bump effect (bum:scale)

	char			*texture_path;       // File path to texture map (txm)
	void			*texture_img;        // Pointer to loaded texture image
	
	char			*bump_path;          // File path to bump map (bum)
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
	float			half_height;
	float			half_width;
	vec3			right;
	vec3			up;
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
	color			color;
	float			dia;
	vec3			pos;
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

void	*generate_entity(void *src, ent_type type);

typedef struct	s_scene scene;

void	add_light(scene *sc, light l);
void	add_entity(scene *sc, void *ent, ent_type type);

#endif