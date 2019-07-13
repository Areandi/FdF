# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlavreni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/06 16:52:44 by mlavreni          #+#    #+#              #
#    Updated: 2019/01/06 16:52:47 by mlavreni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf

# files
SRC		= main.c \
			file_reader.c \
			lists.c \
			map.c \
			keyboard.c \
			let_it_draw.c \
			get_color.c \
			rotate.c 

OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

# compiler
CC		= gcc
CFLAGS	=  -g

# mlx library
MLX_LNK	= -lmlx -framework OpenGL -framework AppKit

# ft library
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft/
FT_LNK	= -L ./libft/ -lft

# directories
SRCDIR	= ./files/
INCDIR	= ./includes/
OBJDIR	= ./obj/

all: obj $(FT_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC)  $(FT_INC) -I ./get_next_line/ -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME) 

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf get_next_line/get_next_line.o
	make -C $(FT) fclean

re: fclean all
