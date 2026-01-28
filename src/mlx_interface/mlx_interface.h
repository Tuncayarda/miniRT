/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_interface.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:23:55 by tuaydin           #+#    #+#             */
/*   Updated: 2026/01/28 19:13:29 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_INTERFACE_H
# define MLX_INTERFACE_H

# include <stdlib.h>
# include <mlx.h>
# include "color.h"
# include "vector.h"

# ifdef __APPLE__
#  define KEY_ESC			53
#  define KEY_W				13
#  define KEY_A				0
#  define KEY_S      1
#  define KEY_D      2
#  define KEY_Z      6
#  define KEY_X      7
#  define KEY_K      40
#  define KEY_L      37
#  define KEY_R      15
#  define KEY_LEFT   123
#  define KEY_RIGHT  124
#  define KEY_UP     126
#  define KEY_DOWN   125
# else
#  define KEY_ESC    0xff1b
#  define KEY_W      0x0077
#  define KEY_A      0x0061
#  define KEY_S      0x0063
#  define KEY_D      0x0064
#  define KEY_Z      0x007a
#  define KEY_X      0x0078
#  define KEY_K      0x006b
#  define KEY_L      0x006c
#  define KEY_R      0x0072
#  define KEY_LEFT   0xff51
#  define KEY_RIGHT  0xff53
#  define KEY_UP     0xff52
#  define KEY_DOWN   0xff54
# endif

# define MOVE_STEP       0.25f
# define ANGLE_STEP_DEG  5.0f
# define FOV_STEP_DEG    5

typedef struct s_scene	t_scene;

typedef struct s_mlx
{
	void		*ptr;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}					t_mlx;

void	put_pix(t_mlx *m, size_t x, size_t y, t_color color);
void	reset_scene(t_scene *sc);
void	recalc_camera(t_scene *sc);
int		on_key(int key, void *param);
int		destroy_prog(void *param);

t_vec3	rotate_around_axis(t_vec3 v, t_vec3 axis, float angle_rad);

#endif