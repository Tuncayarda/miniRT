#ifndef __MLX_INTERFACE_H__
# define __MLX_INTERFACE_H__

# include <stdlib.h>
# include <mlx.h>
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

void	put_pix(mlx *m, size_t x, size_t y, color color);

#endif