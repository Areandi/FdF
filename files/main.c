/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavreni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 14:06:46 by mlavreni          #+#    #+#             */
/*   Updated: 2018/12/20 14:13:21 by mlavreni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_params	*create_params(t_map *map)
{
	t_params	*params;

	if (!(params = (t_params*)malloc(sizeof(t_params))))
		return (0);
	params->mlx_ptr = mlx_init();
	params->win_ptr = mlx_new_window(params->mlx_ptr,
		WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	params->map = map;
	params->view = create_view();
	params->image = create_image(params);
	return (params);
}

char		*trashless_join(char *s1, char *s2)
{
	char	*line;

	line = ft_strjoin(s1, s2);
	free(s2);
	return (line);
}

void		draw_props(t_params *params)
{
	char	*line;

	line = trashless_join("X: ", ft_itoa(params->view->x_angle));
	mlx_string_put(params->mlx_ptr, params->win_ptr, 46, 20, 0xFFFFFF, line);
	free(line);
	line = trashless_join("Y: ", ft_itoa(params->view->y_angle));
	mlx_string_put(params->mlx_ptr, params->win_ptr, 46, 40, 0xFFFFFF, line);
	free(line);
	line = trashless_join("Z: ", ft_itoa(params->view->z_angle));
	mlx_string_put(params->mlx_ptr, params->win_ptr, 46, 60, 0xFFFFFF, line);
	free(line);
	line = trashless_join("Scale: ", ft_itoa(params->view->scale));
	mlx_string_put(params->mlx_ptr, params->win_ptr, 22, 80, 0xFFFFFF, line);
	free(line);
	line = trashless_join("X offset: ", ft_itoa(params->view->x_offset));
	mlx_string_put(params->mlx_ptr, params->win_ptr, 3, 100, 0xFFFFFF, line);
	free(line);
	line = trashless_join("Y offset: ", ft_itoa(params->view->y_offset));
	mlx_string_put(params->mlx_ptr, params->win_ptr, 3, 120, 0xFFFFFF, line);
	free(line);
}

int			red_button(void)
{
	exit(0);
}

int			main(int ac, char **av)
{
	t_map		*map;
	t_params	*params;
	int			fd;

	if (ac < 2)
		return (ft_putstr("USAGE: ./fdf file [ depth | flat | hight color]\n"));
	fd = open(av[1], O_RDONLY);
	if (fd < 0 || !(file_reader(fd, &map, ac, av)))
		return (ft_putstr("ERROR: invalid file\n"));
	params = create_params(map);
	render_map(params);
	mlx_hook(params->win_ptr, 2, 1L, key_press, params);
	mlx_hook(params->win_ptr, 17, 0, red_button, params);
	mlx_loop(params->mlx_ptr);
	return (0);
}
