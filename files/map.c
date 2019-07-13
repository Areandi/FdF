/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavreni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 14:44:14 by mlavreni          #+#    #+#             */
/*   Updated: 2019/01/06 14:44:20 by mlavreni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_map		*create_map(int width, int height)
{
	t_map	*map;
	t_dot	**dots;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (NULL);
	map->width = width;
	map->height = height;
	if (!(dots = (t_dot**)malloc(sizeof(t_dot*) * width * height)))
		return (NULL);
	map->dots = dots;
	map->max_depth = 0;
	map->min_depth = 0;
	map->color_1 = 0x66FF33;
	map->color_2 = 0xCDCD00;
	map->color_3 = 0xCC3300;
	return (map);
}

void		set_color(t_map *map)
{
	int		x;
	int		y;
	t_dot	*dot;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			dot = map->dots[y * map->width + x];
			if (dot->z == 0)
				dot->color = rgb_magic(map->color_2, map->color_2,
					percent(map->min_depth, map->max_depth, dot->z));
			else if (dot->z > 0)
				dot->color = rgb_magic(map->color_2, map->color_1,
					percent(map->min_depth, map->max_depth, dot->z));
			else
				dot->color = rgb_magic(map->color_3, map->color_2,
					percent(map->min_depth, map->max_depth, dot->z));
		}
	}
}

t_dot		f(int x, int y, t_map *map)
{
	return (*map->dots[y * map->width + x]);
}

void		find_depth(t_map *map)
{
	int		x;
	int		y;
	int		max;
	int		min;
	t_dot	dot;

	max = -100;
	min = 100;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			dot = f(x, y, map);
			if (dot.z > max)
				max = dot.z;
			if (dot.z < min)
				min = dot.z;
		}
	}
	map->max_depth = max;
	map->min_depth = min;
}

int			fill_map(t_map **map, t_lst *list)
{
	char	**z_line;
	int		len;
	int		x;
	int		y;

	len = ft_count_words(list->item, ' ');
	y = -1;
	while (++y < (*map)->height)
	{
		if ((z_line = ft_strsplit(list->item, ' ')) == NULL)
			return (0);
		x = -1;
		while (++x < (*map)->width)
		{
			if (!(ft_is_line_digit(z_line[x])))
				return (ultimate_cleaner(&list, map, z_line));
			(*map)->dots[y * (*map)->width + x] = create_dot(x, y, z_line[x]);
			free(z_line[x]);
		}
		free(z_line);
		list = list->next;
	}
	return (1);
}
