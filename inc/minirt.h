#ifndef __MINI_RT__
# define __MINI_RT__

# define WIDTH	1280.0f
# define HEIGHT	720.0f
# define ASPECT_RATIO WIDTH / HEIGHT

# define ERROR_MSG_DFL "Error\n"

# include "entities.h"
# include "gc.h"
# include "mlx_interface.h"

typedef struct	s_skybox
{
	bool			has_skybox;

	int				tex_width;
	int				tex_height;
	int				tex_bpp;
	int				tex_line_len;
	int				tex_endian;
	char			*tex_addr;

	char			*texture_path;
	void			*texture_img;
}				t_skybox;

typedef struct s_scene
{
	t_ambient_light		ambient;
	t_camera			cam;
	t_light				*lights;
	t_entity			*ents;
	size_t				light_count;
	size_t				ent_count;
	t_skybox			sky;
	t_mlx					mlx;
	char				**av;
}						t_scene;

#endif
