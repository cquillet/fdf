/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 16:29:53 by cquillet          #+#    #+#             */
/*   Updated: 2017/10/16 15:38:49 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

int		quit_error(const char *s, t_map *map)
{
	ft_putstr(s);
	if (map)
		del_map(map);
	ft_putstr("usage: fdf MAP_FILE\n");
	return (-1);
}

int		exit_fdf(t_fdf *fdf)
{
	del_map(&(fdf->map));
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.win.img.ptr);
	mlx_destroy_window(fdf->mlx.mlx, fdf->mlx.win.win);
	return (0);
}

int		close_and_del_map(const int fd, t_map *map)
{
	close(fd);
	del_map(map);
	return (-1);
}

int		close_and_del2dim(const int fd, void ***ptr, unsigned int n)
{
	close(fd);
	if (ptr)
		ft_memdel2dim(ptr, n);
	return (-1);
}

t_pixel	conv_3d_to_pixel(t_3d point, unsigned int color, t_proj proj)
{
	t_vector		v;
	t_pixel			p;

	v = create_vector((double)point.x, (double)point.y,
												proj.korr_z * (double)point.z);
	v = vect_rot(v, proj.rot);
	p.x = (int)((v.x - v.y) * proj.zoom);
	p.y = (int)((v.x / 2. + v.y / 2. - v.z) * proj.zoom);
	p.color = color;
	return (p);
}
