/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mouse_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:55:01 by cquillet          #+#    #+#             */
/*   Updated: 2017/10/06 18:46:10 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_mouse_macos.h"
#include "fdf.h"

int		mouse_event(int button, int x, int y, void *param)
{
	t_fdf	*fdf;
	t_proj	*proj;
	double	d;

	fdf = (t_fdf *)param;
	proj = &(fdf->proj);
	d = COEFF_ZOOM;
	if (button == MOUSE_ROLL_FRONT)
		proj->zoom /= d;
	else if (button == MOUSE_ROLL_BACK)
		proj->zoom *= d;
	if (x || y)
		;
	clear_img(&(fdf->mlx.win.img));
	simple_iso(fdf);
	return (button);
}
