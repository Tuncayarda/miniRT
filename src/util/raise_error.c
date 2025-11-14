/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raise_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:26:58 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:26:59 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "libft.h"

void	raise_error(t_scene *sc, const char *msg)
{
	(void)sc;
	gc_manager(NULL, MODE_FREE);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(1);
}
