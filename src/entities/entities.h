#ifndef ENTITIES_H
# define ENTITIES_H

# include <stdlib.h>
# include <stdbool.h>
# include "vector.h"
# include "color.h"

typedef enum e_ent_type
{
	ENT_SPHERE,
	ENT_PLANE,
	ENT_CYLINDER,
	ENT_CIRCLE,
	ENT_UNKNOWN
}					t_ent_type;

typedef struct s_material
{
	bool			has_spc;
	bool			has_checker;
	bool			has_texture;
	bool			has_bump;

	float			specular_strength;
	float			shininess;

	t_color			checker_color;
	float			checker_scale;

	float			texture_scale;
	float			bump_strength;

	char			*texture_path;
	void			*texture_img;

	char			*bump_path;
	void			*bump_img;
}					t_material;

typedef struct s_entity
{
	t_ent_type		type;
	void			*ent;
}					t_entity;

typedef struct s_ambient_light
{
	float			ratio;
	t_color			color;
}					t_ambient_light;

typedef struct s_camera
{
	t_vec3			pos;
	t_vec3			dir;
	__uint8_t		fov;
	float			half_height;
	float			half_width;
	t_vec3			right;
	t_vec3			up;
}					t_camera;

typedef enum e_light_type
{
	LIGHT_POINT,
	LIGHT_SPOT,
}					t_light_type;

typedef struct s_light
{
	t_vec3			pos;
	t_color			color;
	float			ratio;
	t_light_type	type;
	t_vec3			dir;
	float			angle;
}					t_light;

typedef struct s_sphere
{
	t_color			color;
	float			dia;
	t_vec3			pos;
	t_material		mat;
}					t_sphere;

typedef struct s_plane
{
	t_vec3			pos;
	t_vec3			axis;
	t_color			color;
	t_material		mat;
}					t_plane;

typedef struct s_circle
{
	t_vec3			pos;
	t_vec3			axis;
	float			radius;
	t_color			color;
	t_material		mat;
}					t_circle;

typedef struct s_cylinder
{
	t_vec3			pos;
	t_vec3			axis;
	t_color			color;
	float			dia;
	float			h;
	t_circle		top;
	t_circle		bottom;
	t_material		mat;
}					t_cylinder;

void	*generate_entity(void *src, t_ent_type type);

typedef struct s_scene	t_scene;

void	add_light(t_scene *sc, t_light l);
void	add_entity(t_scene *sc, void *ent, t_ent_type type);

#endif