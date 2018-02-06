/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 18:07:00 by cquillet          #+#    #+#             */
/*   Updated: 2017/10/05 16:38:03 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECTION_H
# define PROJECTION_H

# include "quat_vector.h"
# include "pixel.h"

typedef struct	s_proj
{
	int			width;
	int			height;
	double		zoom;
	t_vector	axis;
	double		angle;
	t_quat		rot;
	double		korr_z;
	t_pixel		offset;
	int			color_id;
}				t_proj;

void			init_proj(t_proj *p);

#endif
