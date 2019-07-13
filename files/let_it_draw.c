/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   let_it_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavreni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 15:24:09 by mlavreni          #+#    #+#             */
/*   Updated: 2019/01/06 15:24:11 by mlavreni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_image		*create_image(t_params *params)
{
	t_image	*image;

	if (!(image = (t_image*)malloc(sizeof(t_image))))
		return (0);
	image->image = mlx_new_image(params->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	image->ptr = mlx_get_data_addr(image->image,
		&image->bpp, &image->stride, &image->endian);
	return (image);
}

t_view		*create_view(void)
{
	t_view	*view;

	if (!(view = (t_view*)malloc(sizeof(t_view))))
		return (0);
	view->x_angle = -1;
	view->y_angle = 0;
	view->z_angle = 1;
	view->scale = 20;
	view->x_offset = WINDOW_WIDTH / 2;
	view->y_offset = WINDOW_HEIGHT / 2;
	return (view);
}

void		prepere_line(t_dot d1, t_dot d2, t_image *image)
{
	t_line	line;

	d1.x = (int)d1.x;
	d1.y = (int)d1.y;
	d2.x = (int)d2.x;
	d2.y = (int)d2.y;
	line.dx = abs((int)d2.x - (int)d1.x);
	line.dy = abs((int)d2.y - (int)d1.y);
	line.sx = d1.x < d2.x ? 1 : -1;
	line.sy = d1.y < d2.y ? 1 : -1;
	line.error = (line.dx > line.dy ? line.dx : -line.dy) / 2;
	draw_line(d1, d2, image, line);
}

void		draw_line(t_dot d1, t_dot d2, t_image *image, t_line line)
{
	t_dot	start;
	t_dot	end;
	int		tmp;

	start = d1;
	end = d2;
	while (!(d1.x == d2.x && d1.y == d2.y))
	{
		if (d1.y <= WINDOW_HEIGHT - 1 && d1.x <= WINDOW_WIDTH - 1
			&& d1.x > 0 && d1.y > 0)
			*(int*)(image->ptr + (((int)d1.y * WINDOW_WIDTH + (int)d1.x) * 4)) =
				get_color(d1, start, end, line);
		tmp = line.error;
		if (tmp > -line.dx)
		{
			line.error -= line.dy;
			d1.x += line.sx;
		}
		if (tmp < line.dy)
		{
			line.error += line.dx;
			d1.y += line.sy;
		}
	}
}

void		render_map(t_params *params)
{
	t_map	*map;
	t_dot	dot;
	t_image	*img;
	int		x;
	int		y;

	map = params->map;
	img = create_image(params);
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			dot = set_dot_props(*map->dots[y * map->width + x], params);
			if (x + 1 < map->width)
				prepere_line(dot, set_dot_props(f(x + 1, y, map), params), img);
			if (y + 1 < map->height)
				prepere_line(dot, set_dot_props(f(x, y + 1, map), params), img);
		}
	}
	mlx_put_image_to_window(params->mlx_ptr, params->win_ptr, img->image, 0, 0);
	draw_props(params);
	mlx_destroy_image(params->mlx_ptr, img->image);
	free(img);
}
