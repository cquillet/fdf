/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 20:49:54 by cquillet          #+#    #+#             */
/*   Updated: 2017/10/16 16:55:30 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "fdf.h"
#include "get_next_line.h"

static int		valid_coord(char *s)
{
	if (*s == '-' || *s == '+')
		s++;
	while (ft_isdigit(*s))
		s++;
	if (*s == '\0')
		return (1);
	if (*s != ',')
		return (0);
	s++;
	if (ft_strcmp(s, "0") == 'x')
		return ((unsigned int)ft_atoi_base(s + 2, 16) <= 0xFFFFFF);
	return ((unsigned int)ft_atoi_base(s, 10) <= 0xFFFFFF);
}

static int		test_x_values(char ***x, t_map *map)
{
	int			i;

	i = 0;
	while (i < map->width && valid_coord((*x)[i]))
		i++;
	ft_memdel2dim((void ***)x, map->width + 1);
	return (i);
}

int				check_map(t_map *map)
{
	int			fd;
	char		*line;
	int			width;
	char		**x;

	if ((fd = open(map->name, O_RDONLY)) < 0)
		return (-1);
	width = -1;
	while ((get_next_line(fd, &line)) > 0)
	{
		x = ft_strsplit(line, ' ');
		ft_memdel((void **)&line);
		if (!x)
			return (close(fd));
		map->width = ft_memlen(x, sizeof(char *));
		if (map->width == 0 || (width != map->width && width > 0))
			return (close_and_del2dim(fd, (void ***)&x, map->width + 1));
		if (test_x_values(&x, map) != (width = map->width))
			return (close(fd));
		map->height++;
	}
	ft_memdel((void **)&line);
	return ((close(fd) < 0) ? -1 : map->height);
}
