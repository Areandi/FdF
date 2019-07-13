/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavreni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 15:25:34 by mlavreni          #+#    #+#             */
/*   Updated: 2019/01/06 15:25:35 by mlavreni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

double	percent(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int		get_light(int start, int end, double p)
{
	return ((int)((1 - p) * start + p * end));
}

int		rgb_magic(int start_color, int end_color, double p)
{
	int		red;
	int		green;
	int		blue;

	red = get_light((start_color >> 16) & 0xFF, (end_color >> 16) & 0xFF, p);
	green = get_light((start_color >> 8) & 0xFF, (end_color >> 8) & 0xFF, p);
	blue = get_light(start_color & 0xFF, end_color & 0xFF, p);
	return ((red << 16) | (green << 8) | blue);
}

int		get_color(t_dot current, t_dot start, t_dot end, t_line line)
{
	double	percentage;

	if (current.color == end.color)
		return (current.color);
	if (line.dx > line.dy)
		percentage = percent(start.x, end.x, current.x);
	else
		percentage = percent(start.y, end.y, current.y);
	return (rgb_magic(start.color, end.color, percentage));
}
