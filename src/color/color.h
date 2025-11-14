/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:22:45 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:22:48 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

typedef union u_color
{
	struct
	{
		__uint8_t	b;
		__uint8_t	g;
		__uint8_t	r;
	};
	__uint32_t		val;
}					t_color;

t_color	color_add(t_color a, t_color b);
t_color	color_modul(t_color a, t_color b);
t_color	color_scale(t_color clr, float intensity);
#endif
