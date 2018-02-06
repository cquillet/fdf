/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 21:02:33 by cquillet          #+#    #+#             */
/*   Updated: 2017/10/17 16:05:28 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "tab_bin.h"
#include "get_next_line.h"

static int		get_hex_color_after_coord(t_map *m, int x, int y, char *s)
{
	char		*hex;

	if (!(hex = ft_strchr(s, ',')))
	{
		let_bin(m->color_forced, y * m->width + x, 0);
		return (0);
	}
	if (!ft_strncmp(hex, ",0x", 3))
	{
		m->color[y][x] = (uint32_t)ft_atoi_base(hex + 3, 16);
		if (m->color[y][x] <= 0xFFFFFF)
			return (let_bin(m->color_forced, y * m->width + x, 1));
		return (let_bin(m->color_forced, y * m->width + x, 0));
	}
	m->color[y][x] = (uint32_t)ft_atoi_base(hex + 1, 10);
	if (m->color[y][x] <= 0xFFFFFF)
		return (let_bin(m->color_forced, y * m->width + x, 1));
	return (let_bin(m->color_forced, y * m->width + x, 0));
}

static int		get_x_values(char **line, t_map *m, int y)
{
	int			i;
	char		**x;

	if (!(m->z[y] = (int *)malloc(m->width * sizeof(int))))
		return (-1);
	if (!(m->color[y] = (uint32_t *)malloc(m->width * sizeof(uint32_t))))
		return (-1);
	x = ft_strsplit(*line, ' ');
	ft_memdel((void **)line);
	i = -1;
	while (x[++i])
	{
		m->z[y][i] = ft_atoi(x[i]);
		if ((!y && !i) || m->z[y][i] > m->z_max)
			m->z_max = m->z[y][i];
		if ((!y && !i) || m->z[y][i] < m->z_min)
			m->z_min = m->z[y][i];
		get_hex_color_after_coord(m, i, y, x[i]);
	}
	ft_memdel2dim((void ***)&x, m->width + 1);
	return (0);
}

int				get_map(t_map *m)
{
	int			fd;
	char		*line;
	int			ret;
	int			y;

	if (m->width <= 1 && m->height <= 1)
		return (-1);
	if ((fd = open(m->name, O_RDONLY)) < 0)
		return (-1);
	if (!(m->z = (int **)malloc(m->height * sizeof(int *))))
		return (-1);
	if (!(m->color = (uint32_t **)malloc(m->height * sizeof(uint32_t *))))
		return (-1);
	if (!(m->color_forced = create_tab_bin(m->height * m->width)))
		return (-1);
	y = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
		if (get_x_values(&line, m, y++) < 0)
		{
			close(fd);
			return (-1);
		}
	ft_memdel((void **)&line);
	return ((close(fd) < 0 || ret < 0) ? -1 : 0);
}
