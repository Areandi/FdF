/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavreni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 13:44:28 by mlavreni          #+#    #+#             */
/*   Updated: 2018/12/24 13:44:33 by mlavreni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_dot	*create_dot(int x, int y, char *z)
{
	t_dot	*dot;

	if (!(dot = (t_dot*)malloc(sizeof(t_dot))))
		return (NULL);
	dot->x = x;
	dot->y = y;
	dot->z = ft_atoi(z);
	dot->color = 0xFFFFFF;
	return (dot);
}

int		useful_arguments(char **av, t_map **map)
{
	int		i;

	i = 1;
	while (++i < 5 && *av[i] != '\0')
		if (!(ft_is_hex(av[i])))
			return (ft_putstr("WARNIGNG: its not hex, try again sweaty <3\n"));
	(*map)->color_1 = ft_htoi(av[2]);
	(*map)->color_2 = ft_htoi(av[3]);
	(*map)->color_3 = ft_htoi(av[4]);
	return (1);
}

int		file_reader(int fd, t_map **map, int ac, char **av)
{
	t_lst	*list;

	list = NULL;
	if (!(fill_list(fd, &list)))
		return (0);
	*map = create_map(ft_count_words(list->item, ' '), list_quantity(list));
	if (!(fill_map(map, list)))
		return (ultimate_cleaner(&list, map, NULL));
	find_depth(*map);
	if (ac == 5)
		useful_arguments(av, map);
	set_color(*map);
	ultimate_cleaner(&list, NULL, NULL);
	return (1);
}
