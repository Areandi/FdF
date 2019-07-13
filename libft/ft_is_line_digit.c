/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_line_digit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavreni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 17:37:10 by mlavreni          #+#    #+#             */
/*   Updated: 2019/01/06 17:37:18 by mlavreni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_is_line_digit(char const *line)
{
	int	flag;

	flag = 0;
	while (*line)
	{
		if ((ft_isdigit(*line)) || *line == '-')
			flag = 1;
		line++;
	}
	if (flag)
		return (1);
	else
		return (0);
}
