#ifndef __MLX_INTERFACE_H__
# define __MLX_INTERFACE_H__

# include <stdlib.h>
# include <mlx.h>
# include "color.h"
# include "vector.h"

# define KEY_ESC    53
# define KEY_W      13
# define KEY_A      0
# define KEY_S      1
# define KEY_D      2
# define KEY_Z      6
# define KEY_X      7
# define KEY_K      40
# define KEY_L      37
# define KEY_R		15
# define KEY_LEFT   123
# define KEY_RIGHT  124
# define KEY_UP     126
# define KEY_DOWN   125

# define MOVE_STEP       0.25f
# define ANGLE_STEP_DEG  5.0f
# define FOV_STEP_DEG    5

typedef struct			s_scene	scene;

typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				mlx;

void	put_pix(mlx *m, size_t x, size_t y, t_color color);

void	reset_scene(scene *sc);
void	recalc_camera(scene *sc);
t_vec3	rotate_around_axis(t_vec3 v, t_vec3 axis, float angle_rad);
int		on_key(int key, void *param);

#endif