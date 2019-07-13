/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavreni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 15:26:53 by mlavreni          #+#    #+#             */
/*   Updated: 2019/01/06 15:29:30 by mlavreni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	rotate_x(t_dot *dot, double angle)
{
	double y;
	double z;

	y = dot->y;
	z = dot->z;
	dot->y = y * cos(angle) + z * sin(angle);
	dot->z = -y * sin(angle) + z * cos(angle);
}

void	rotate_y(t_dot *dot, double angle)
{
	double x;
	double z;

	x = dot->x;
	z = dot->z;
	dot->x = x * cos(angle) + z * sin(angle);
	dot->z = -x * sin(angle) + z * cos(angle);
}

void	rotate_z(t_dot *dot, double angle)
{
	double x;
	double y;

	x = dot->x;
	y = dot->y;
	dot->x = x * cos(angle) - y * sin(angle);
	dot->y = x * sin(angle) + y * cos(angle);
}

t_dot	set_dot_props(t_dot dot, t_params *params)
{
	dot.x -= (double)(params->map->width) / 2.0f;
	dot.y -= (double)(params->map->height) / 2.0f;
	rotate_z(&dot, params->view->z_angle);
	rotate_y(&dot, params->view->y_angle);
	rotate_x(&dot, params->view->x_angle);
	dot.x *= params->view->scale;
	dot.y *= params->view->scale;
	dot.x += params->view->x_offset;
	dot.y += params->view->y_offset;
	return (dot);
}
