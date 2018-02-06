/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 19:33:03 by cquillet          #+#    #+#             */
/*   Updated: 2017/10/22 19:40:11 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"
#include "colors.h"
#include "mlx_img.h"
#include "scale.h"
#include "pixel.h"

void			draw_map_caption(t_fdf *fdf)
{
	int		n;
	char	s[15][50];
	int		delta_y;
	t_pixel	p;

	n = 0;
	strcpy(s[n++], "Axis |   navigate    |  rotation |");
	strcpy(s[n++], "-----+---------------+-----------|");
	strcpy(s[n++], "  X  | A / D   < / > |   1 / 3   |");
	strcpy(s[n++], s[1]);
	strcpy(s[n++], "  Y  | W / S   ^ / v |   4 / 6   |");
	strcpy(s[n++], s[1]);
	strcpy(s[n++], "  Z  | - / +   2 / 8 |   7 / 9   |");
	strcpy(s[n++], "---------------------------------");
	strcpy(s[n++], "");
	strcpy(s[n++], "Change color : C");
	strcpy(s[n++], "");
	strcpy(s[n++], "Reset zoom : Space");
	delta_y = 11;
	p = create_pixel(5, delta_y * (n - 1), 0xFFFFFF);
	while (n--)
	{
		mlx_string_put(fdf->mlx.mlx, fdf->mlx.win.win, p.x, p.y, p.color, s[n]);
		p.y -= delta_y;
	}
}

void			draw_map(t_fdf *fdf)
{
	int		i;
	int		j;
	t_pixel	p;
	t_mlx	*mlx;
	t_map	m;

	mlx = &(fdf->mlx);
	m = fdf->map;
	i = -1;
	while (++i < m.height)
	{
		p.y = scale(i, create_2d(0, m.height), create_2d(0, mlx->win.height));
		j = -1;
		while (++j < m.width)
		{
			p.x = scale(j, create_2d(0, m.width), create_2d(0, mlx->win.width));
			if (m.color[i][j] > 0xFFFFFF)
				p.color = scale(m.z[i][j], create_2d(m.z_min, m.z_max),
													create_2d(0x01, 0xFFFFFF));
			else
				p.color = m.color[i][j];
			put_pixel_in_img(mlx->mlx, mlx, p);
		}
	}
	draw_img(mlx->mlx, mlx->win.win, mlx->win.img);
}
