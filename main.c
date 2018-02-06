/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 03:05:56 by cquillet          #+#    #+#             */
/*   Updated: 2017/10/16 11:22:56 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "fdf.h"
#include "draw.h"

int		main(int ac, char **av)
{
	t_fdf		fdf;

	if (ac != 2)
		return (quit_error(ac < 2 ? "NO FILE\n" : "TOO MUCH ARGS\n", NULL));
	fdf.map = create_empty_map(av[1]);
	if ((fdf.map.height = check_map(&(fdf.map))) < 1)
		return (quit_error("MAP ERROR\n", &fdf.map));
	if (get_map(&fdf.map) < 0)
		return (quit_error("MAP ERROR\n", &fdf.map));
	fdf.mlx = create_mlx(mlx_init(), WIN_WIDTH, WIN_HEIGTH);
	fdf.mlx.win = create_win(&fdf.mlx, fdf.map.name, fdf.mlx.width,
																fdf.mlx.height);
	fdf.mlx.win.img = init_img(fdf.mlx.mlx, fdf.mlx.win.width,
															fdf.mlx.win.height);
	init_proj(&(fdf.proj));
	color_map(&(fdf.map), fdf.proj.color_id);
	init_iso(&fdf);
	simple_iso(&fdf);
	mlx_key_hook(fdf.mlx.win.win, key_event, &fdf);
	mlx_mouse_hook(fdf.mlx.win.win, mouse_event, &fdf);
	mlx_loop(fdf.mlx.mlx);
	return (0);
}
