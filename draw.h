/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 18:16:20 by cquillet          #+#    #+#             */
/*   Updated: 2017/10/16 11:18:49 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "fdf.h"

# ifndef NB_MAP_COLORS
#  define NB_MAP_COLORS 5
# endif

unsigned int	color_func(int color_index, int v, int min, int max);
void			color_map(t_map *m, int color_index);
void			draw_map(t_fdf *fdf);
void			draw_map_caption(t_fdf *fdf);

#endif
