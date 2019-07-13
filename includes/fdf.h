/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavreni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 12:35:58 by mlavreni          #+#    #+#             */
/*   Updated: 2018/12/21 12:36:00 by mlavreni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 800
# define ESC_KEY 53
# define A_KEY 0
# define W_KEY 13
# define S_KEY 1
# define D_KEY 2
# define Q_KEY 12
# define E_KEY 14
# define R_KEY 15
# define F_KEY 3
# define UP_ARROW 126
# define LEFT_ARROW 123
# define DOWN_ARROW 125
# define RIGHT_ARROW 124

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "mlx.h"
# include "../libft/libft.h"

typedef struct			s_dot
{
	double				x;
	double				y;
	double				z;
	int					color;
}						t_dot;

typedef struct			s_line
{
	int					x;
	int					y;
	int					dx;
	int					dy;
	int					sx;
	int					sy;
	int					error;
	t_dot				start;
	t_dot				end;
}						t_line;

typedef struct			s_map
{
	int					width;
	int					height;
	int					max_depth;
	int					min_depth;
	int					color_1;
	int					color_2;
	int					color_3;
	t_dot				**dots;
}						t_map;

typedef struct			s_lst
{
	char				*item;
	struct s_lst		*next;
}						t_lst;

typedef struct			s_image
{
	void				*image;
	char				*ptr;
	int					bpp;
	int					stride;
	int					endian;
}						t_image;

typedef struct			s_view
{
	double				x_angle;
	double				y_angle;
	double				z_angle;
	int					scale;
	double				x_offset;
	double				y_offset;
}						t_view;

typedef struct			s_params
{
	void				*mlx_ptr;
	void				*win_ptr;
	int					x;
	int					y;
	t_map				*map;
	t_view				*view;
	t_image				*image;
}						t_params;

double					percent(int start, int end, int current);
int						get_light(int start, int end, double percentage);
int						rgb_magic(int start_color, int end_color, double p);
int						get_color(t_dot curr, t_dot start, t_dot end, t_line l);
t_dot					*create_dot(int x, int y, char *z);
t_map					*create_map(int width, int height);
t_image					*create_image(t_params *params);
t_view					*create_view(void);
t_params				*create_params(t_map *map);
int						list_quantity(t_lst *list);
int						list_add(t_lst **list, t_lst *item);
int						ultimate_cleaner(t_lst **list, t_map **map, char **l);
t_lst					*create_item(char *item);
int						fill_list(int fd, t_lst **list);
int						fill_map(t_map **map, t_lst *list);
void					find_depth(t_map *map);
void					set_color(t_map *map);
int						file_reader(int fd, t_map **map, int ac, char **av);
void					draw_line(t_dot d1, t_dot d2, t_image *image, t_line l);
void					prepere_line(t_dot d1, t_dot d2, t_image *image);
void					draw_props(t_params *params);
void					rotate_x(t_dot *dot, double anle);
void					rotate_y(t_dot *dot, double anle);
void					rotate_z(t_dot *dot, double anle);
t_dot					set_dot_props(t_dot dot, t_params *params);
void					render_map(t_params *params);
void					key_letters(int key, t_params *params);
void					key_arrows(int key, t_params *params);
int						key_press(int key, t_params *params);
t_dot					f(int x, int y, t_map *map);

#endif
