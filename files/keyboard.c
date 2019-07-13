/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavreni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 15:16:54 by mlavreni          #+#    #+#             */
/*   Updated: 2019/01/06 15:16:55 by mlavreni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	keys_letters(int key, t_params *params)
{
	if (key == W_KEY)
		params->view->x_angle += 0.1;
	else if (key == S_KEY)
		params->view->x_angle -= 0.1;
	else if (key == A_KEY)
		params->view->y_angle += 0.1;
	else if (key == D_KEY)
		params->view->y_angle -= 0.1;
	else if (key == E_KEY)
		params->view->z_angle += 0.1;
	else if (key == Q_KEY)
		params->view->z_angle -= 0.1;
	else if (key == R_KEY)
		params->view->scale += 1;
	else if (key == F_KEY)
		params->view->scale -= 1;
	render_map(params);
}

void	keys_arrows(int key, t_params *params)
{
	if (key == RIGHT_ARROW)
		params->view->x_offset += 20;
	else if (key == LEFT_ARROW)
		params->view->x_offset -= 20;
	else if (key == DOWN_ARROW)
		params->view->y_offset += 20;
	else if (key == UP_ARROW)
		params->view->y_offset -= 20;
	render_map(params);
}

int		key_press(int key, t_params *params)
{
	if (key == ESC_KEY)
		exit(0);
	keys_letters(key, params);
	keys_arrows(key, params);
	return (0);
}
