/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 06:53:16 by cquillet          #+#    #+#             */
/*   Updated: 2018/02/06 15:46:42 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "vector.h"
#include "pixel.h"
#include "box.h"
#include <math.h>
#include "libft.h"
#include "quat_vector.h"
#include "draw.h"

/*
** X = a.x - b.y
** Y = a.x/2 + b.y/2 + z
*/

static t_pixel	place_pix_in_img(t_3d *coord, t_fdf *fdf)
{
	t_pixel		pix;
	uint32_t	color;

	coord->z = fdf->map.z[coord->y][coord->x];
	color = fdf->map.color[coord->y][coord->x];
	pix = conv_3d_to_pixel(*coord, color, fdf->proj);
	pix.x -= (fdf->proj.offset.x);
	pix.y -= (fdf->proj.offset.y);
	put_pixel_in_img(fdf->mlx.mlx, fdf, pix);
	return (pix);
}

static void		connect_with_up(t_3d coord, t_pixel pix, t_pixel *up,
																t_fdf *fdf)
{
	if (coord.y > 0)
		draw_line(&(fdf->mlx), *up, pix);
	if (coord.y < fdf->map.height - 1)
		*up = pix;
}

static t_box	limits_simple_iso(t_fdf fdf)
{
	t_3d	coord;
	t_pixel	pix;
	t_box	box;

	coord.y = 0;
	while (coord.y < fdf.map.height)
	{
		coord.x = 0;
		while (coord.x < fdf.map.width)
		{
			coord.z = fdf.map.z[coord.y][coord.x];
			pix = conv_3d_to_pixel(coord, 0, fdf.proj);
			if (coord.x || coord.y)
				box_redim(&box, pix);
			else
				box = create_box(pix.x, pix.x, pix.y, pix.y);
			coord.x++;
		}
		coord.y++;
	}
	return (box);
}

void			simple_iso(t_fdf *fdf)
{
	t_3d	coord;
	t_pixel	pix;
	t_pixel	*up;
	t_pixel	left;

	if (!(up = (t_pixel *)malloc(fdf->map.width * sizeof(t_pixel))))
		return ;
	coord.y = -1;
	while (++coord.y < fdf->map.height)
	{
		coord.x = -1;
		while (++coord.x < fdf->map.width)
		{
			pix = place_pix_in_img(&coord, fdf);
			if (coord.x > 0)
				draw_line(&(fdf->mlx), left, pix);
			if (coord.x < fdf->map.width - 1)
				left = pix;
			connect_with_up(coord, pix, &(up[coord.x]), fdf);
		}
	}
	ft_memdel((void **)&up);
	draw_img(fdf->mlx.mlx, fdf->mlx.win.win, fdf->mlx.win.img);
	draw_map_caption(fdf);
}

void			init_iso(t_fdf *fdf)
{
	t_box	box;
	double	width_ratio;
	double	height_ratio;

	box = limits_simple_iso(*fdf);
	fdf->proj.offset = create_pixel(box.x_min, box.y_min, 0);
	width_ratio = (double)fdf->mlx.win.width / (double)box_width(box);
	height_ratio = (double)fdf->mlx.win.height / (double)box_height(box);
	if (width_ratio > height_ratio)
	{
		if (ft_absf(0.9 * height_ratio - 1.) > 0.1)
			fdf->proj.zoom *= (0.9 * height_ratio);
	}
	else
	{
		if (ft_absf(0.9 * width_ratio - 1.) > 0.1)
			fdf->proj.zoom *= (0.9 * width_ratio);
	}
	box = limits_simple_iso(*fdf);
	fdf->proj.offset = create_pixel(
				box.x_min - (fdf->mlx.win.width - box_width(box)) / 2,
				box.y_min - (fdf->mlx.win.height - box_height(box)) / 2, 0);
}
