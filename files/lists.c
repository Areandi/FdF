/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavreni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 14:42:01 by mlavreni          #+#    #+#             */
/*   Updated: 2019/01/06 14:42:03 by mlavreni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_lst		*create_item(char *item)
{
	t_lst *list;

	if (!(list = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	list->item = ft_strdup(item);
	list->next = NULL;
	return (list);
}

int			list_quantity(t_lst *list)
{
	t_lst	*current;
	int		i;

	i = 0;
	current = list;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

int			list_add(t_lst **list, t_lst *new)
{
	t_lst *current;

	if (*list == NULL)
	{
		*list = new;
		return (0);
	}
	current = *list;
	while (current != NULL)
		if (current->next != NULL)
			current = current->next;
		else
			break ;
	current->next = new;
	return (0);
}

int			ultimate_cleaner(t_lst **list, t_map **map, char **line)
{
	t_lst	*next;
	int		a;

	while (*list)
	{
		next = (*list)->next;
		ft_memdel((void*)&(*list)->item);
		ft_memdel((void **)list);
		*list = next;
	}
	if (map && *map)
	{
		if (line && *line)
		{
			a = -1;
			while (++a != (*map)->width)
				free(line[a]);
			free(line);
		}
		ft_memdel((void **)&(*map)->dots);
		ft_memdel((void **)map);
	}
	if (line && *line)
		free(*line);
	return (0);
}

int			fill_list(int fd, t_lst **list)
{
	t_lst	*current;
	char	*line;
	int		rat;
	int		len;

	len = -1;
	while ((rat = get_next_line(fd, &line)))
	{
		(len == -1) ? len = ft_count_words(line, ' ') : 0;
		current = create_item(line);
		list_add(list, current);
		if (len != (int)ft_count_words(line, ' '))
			return (ultimate_cleaner(list, NULL, &line));
		if (rat == -1)
			return (0);
		free(line);
	}
	return (1);
}
