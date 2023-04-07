/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 14:13:54 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/04/05 13:14:56 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point	*set_point(t_point *point, int x, int y, char *z_color)
{
	point->x_init = x;
	point->y_init = y;
	point->z_init = ft_atoi(z_color);
	point->x = point->x_init;
	point->y = point->y_init;
	point->z = point->z_init;
	point->color = 0xFFFFFFFF;
	if (ft_strchr(z_color, ','))
		point->color = (hexstring_to_uint(ft_strchr(z_color, ',') + 1) << 8)
			+ 0xFF;
	point->next = NULL;
	point->next_point = NULL;
	point->next_row = NULL;
	return (point);
}

static t_point	*add_pointers(t_point *map)
{
	t_point	*row;
	t_point	*point;

	if (!map)
		return (map);
	if (!map->next)
		free_exit(NULL, NULL, map, ERR_MAP);
	point = map;
	while (point->next)
	{
		if (point->next->x == point->x + 1)
			point->next_point = point->next;
		point = point->next;
	}
	point = map;
	while (point->next)
	{
		row = point->next;
		while (row && point->x != row->x)
			row = row->next;
		point->next_row = row;
		point = point->next;
	}
	return (map);
}

static t_point	*add_point_to_map(t_point **map, t_point *last, t_point *point)
{
	if (!*map)
	{
		*map = point;
		return (point);
	}
	last->next = point;
	return (point);
}

static t_point	*allocate_points(t_point *map,
	char **split_line, int row)
{
	int				x;
	t_point			*point;
	static t_point	*last = NULL;

	x = 0;
	while (split_line[x] && split_line[x][0] != '\n')
	{
		point = (t_point *)malloc(sizeof(t_point));
		if (!point)
		{
			free_split_line(split_line);
			free_exit(NULL, NULL, map, ERR_MALLOC);
		}
		point = set_point(point, x, row, split_line[x]);
		last = add_point_to_map(&map, last, point);
		if (ft_strchr(split_line[x], '\n'))
			break ;
		x++;
	}
	return (map);
}

t_point	*init_map(int fd)
{
	int		row;
	char	*line;
	char	**split_line;
	t_point	*map;

	map = NULL;
	line = get_next_line(fd);
	row = 0;
	while (line)
	{
		split_line = ft_split(line, ' ');
		free(line);
		if (!*split_line)
		{
			free_split_line(split_line);
			free_exit(NULL, NULL, map, ERR_MALLOC);
		}
		map = allocate_points(map, split_line, row++);
		free_split_line(split_line);
		line = get_next_line(fd);
	}
	map = add_pointers(map);
	return (map);
}
