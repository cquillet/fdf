/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_event.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 15:52:28 by cquillet          #+#    #+#             */
/*   Updated: 2017/10/16 11:22:33 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_keys_macos.h"
#include "fdf.h"
#include "projection.h"
#include "quat_vector.h"
#include "draw.h"

static void	rotation(t_proj *proj, t_vector axis, double angle)
{
	proj->rot = quat_mul(proj->rot, quat_rot(axis, angle));
}

static int	key_rot(int key, t_proj *p)
{
	if (key == KEY_PAD_1)
		rotation(p, create_vector(1., 0., 0.), -VAR_ROT);
	else if (key == KEY_PAD_3)
		rotation(p, create_vector(1., 0., 0.), +VAR_ROT);
	else if (key == KEY_PAD_4)
		rotation(p, create_vector(0., 1., 0.), -VAR_ROT);
	else if (key == KEY_PAD_6)
		rotation(p, create_vector(0., 1., 0.), +VAR_ROT);
	else if (key == KEY_PAD_7)
		rotation(p, create_vector(0., 0., 1.), -VAR_ROT);
	else if (key == KEY_PAD_9)
		rotation(p, create_vector(0., 0., 1.), +VAR_ROT);
	else
		return (-1);
	return (key);
}

static int	key_zoom(int key, t_proj *proj)
{
	double	d;

	d = COEFF_ZOOM;
	if (key == KEY_PAD_SUB || key == KEY_PAD_ADD)
		proj->zoom = (key - KEY_PAD_SUB) ? proj->zoom * d : proj->zoom / d;
	else if (key == KEY_PAD_8 || key == KEY_PAD_2)
		proj->korr_z = (key - KEY_PAD_2) ? proj->korr_z * d : proj->korr_z / d;
	else
		return (-1);
	return (key);
}

static int	key_move(int key, t_proj *proj)
{
	double	d;

	d = VAR_MOV;
	if (key == KEY_W || key == KEY_DOWN)
		proj->offset.y += d;
	else if (key == KEY_S || key == KEY_UP)
		proj->offset.y -= d;
	else if (key == KEY_A || key == KEY_RIGHT)
		proj->offset.x += d;
	else if (key == KEY_D || key == KEY_LEFT)
		proj->offset.x -= d;
	else
		return (-1);
	return (key);
}

int			key_event(int key, void *param)
{
	t_fdf	*fdf;
	t_proj	*proj;

	fdf = (t_fdf *)param;
	proj = &(fdf->proj);
	if (key == KEY_ESCAPE)
		exit(exit_fdf(fdf));
	if (key == KEY_SPACEBAR)
		init_iso(fdf);
	else if (key_zoom(key, proj) + 1 || key_move(key, proj) + 1
				|| key_rot(key, proj) + 1)
		;
	else if (key == KEY_C)
		color_map(&(fdf->map), ++proj->color_id);
	else
		return (0);
	clear_img(&(fdf->mlx.win.img));
	simple_iso(fdf);
	return (key);
}
