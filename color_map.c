/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 17:12:30 by cquillet          #+#    #+#             */
/*   Updated: 2017/10/16 15:30:48 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "colors.h"
#include "tab_bin.h"
#include "int_2d.h"
#include "draw.h"

void			color_map(t_map *m, int color_index)
{
	int		i;
	int		j;

	i = 0;
	while (i < m->height)
	{
		j = 0;
		while (j < m->width)
		{
			if (!(get_bin(m->color_forced, (unsigned int)(i * m->width + j))))
			{
				m->color[i][j] =
					color_func(color_index, m->z[i][j], m->z_min, m->z_max);
			}
			j++;
		}
		i++;
	}
}

unsigned int	color_func(int color_index, int v, int min, int max)
{
	color_index %= NB_MAP_COLORS;
	if (color_index == 0)
		return (0x00FF00);
	else if (color_index == 1)
		return (rgb_between(v, create_2d(min, max), 0x0000FF, 0xFF0000));
	else if (color_index == 2)
		return (spectrum_gray(v, min, max));
	else if (color_index == 3)
		return (spectrum_color(v, min, max * 11 / 10));
	else if (color_index == 4)
		return (rgb_earth(v, min, max));
	else
		return (0);
}
