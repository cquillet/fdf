/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 03:45:56 by cquillet          #+#    #+#             */
/*   Updated: 2017/10/06 22:52:56 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "tab_bin.h"
#include "fdf.h"

t_map		create_empty_map(char *name)
{
	t_map	map;

	map.name = name;
	map.width = 0;
	map.height = 0;
	map.z = NULL;
	map.color = NULL;
	map.color_forced = NULL;
	map.z_min = 0;
	map.z_max = 0;
	return (map);
}

int			del_map(t_map *map)
{
	if (map)
	{
		if (map->color_forced)
			ft_memdel((void **)&(map->color_forced));
		if (map->z)
			ft_memdel2dim((void ***)&(map->z), map->height);
		if (map->color)
			ft_memdel2dim((void ***)&(map->color), map->height);
	}
	return (-1);
}
