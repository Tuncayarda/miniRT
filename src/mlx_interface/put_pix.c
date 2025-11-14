/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pix.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:23:59 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:54:56 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "minirt.h"
#include "mlx_interface.h"

void	put_pix(t_mlx *m, size_t x, size_t y, t_color color)
{
	char	*pixel;

	if (x >= WIDTH || y >= HEIGHT)
		return ;
	pixel = m->addr + (y * m->line_len + x * (m->bpp / 8));
	pixel[0] = color.b;
	pixel[1] = color.g;
	pixel[2] = color.r;
	pixel[3] = (char)0;
}
