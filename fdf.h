/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 04:01:33 by cquillet          #+#    #+#             */
/*   Updated: 2017/10/16 11:21:55 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "pixel.h"
# include "int_3d.h"
# include <math.h>
# include <stdlib.h>
# include "mlx_img.h"
# include "box.h"
# include "vector.h"
# include "parsing.h"
# include "projection.h"
# include "graphics.h"

# ifndef VAR_ROT
#  define VAR_ROT (M_PI / 18.)
# endif

# ifndef VAR_MOV
#  define VAR_MOV 20
# endif

# ifndef COEFF_ZOOM
#  define COEFF_ZOOM 1.1
# endif

typedef struct	s_fdf
{
	t_mlx		mlx;
	t_map		map;
	t_proj		proj;
}				t_fdf;

/*
** Events
*/

int				key_event(int key, void *param);
int				mouse_event(int button, int x, int y, void *param);

/*
** Exits
*/

int				exit_fdf(t_fdf *fdf);
int				close_and_del_map(const int fd, t_map *map);
int				close_and_del2dim(const int fd, void ***ptr, unsigned int n);
int				quit_error(const char *s, t_map *map);

/*
** Isometric
*/

void			simple_iso(t_fdf *fdf);
void			init_iso(t_fdf *fdf);
t_pixel			conv_3d_to_pixel(t_3d point, unsigned int color, t_proj proj);

/*
** Boxes
*/

int				box_fills_in_win(t_box b, t_win w);
int				box_fills_in_zone(t_box b, t_zone z);

#endif
