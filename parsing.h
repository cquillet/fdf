/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 17:05:38 by cquillet          #+#    #+#             */
/*   Updated: 2017/10/16 11:18:27 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>

typedef struct	s_map
{
	char		*name;
	int			width;
	int			height;
	int			**z;
	uint32_t	**color;
	char		*color_forced;
	int			z_min;
	int			z_max;
}				t_map;

int				check_map(t_map *map);
void			color_forced_map(t_map *map);
int				get_map(t_map *map);
t_map			create_empty_map(char *name);
int				del_map(t_map *map);

#endif
