# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/09 16:13:19 by cquillet          #+#    #+#              #
#    Updated: 2018/02/10 20:44:06 by cquillet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc

DIRLIBS = ../libs

DIRHEADER = . $(DIRLIBS)/includes
CFLAGS = $(DIRHEADER:%=-I%) -Wall -Wextra -Werror

LDFLAGS = $(DIRLIBS:%=-L%) -framework OpenGL -framework AppKit
CUSTOMLIBS = libft.a libftprintf.a libmlx.a
LIBS = $(CUSTOMLIBS) libm.a
LDLIBS = $(LIBS:lib%.a=-l%)

SRC = check_map.c color_map.c draw.c fdf.c fdf_key_event.c fdf_mouse_event.c \
get_map.c isometric.c main.c parsing.c projection.c

OBJ = $(SRC:%.c=%.o)

RM = rm -f

.PHONY: all clean fclean re libs

all: libs $(NAME)

libs:
	make -C $(DIRLIBS) $(CUSTOMLIBS)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $(LDLIBS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $? -o $@

clean:
	make -C $(DIRLIBS) clean
	$(RM) $(OBJ)

fclean:
	make -C $(DIRLIBS) fclean
	$(RM) $(OBJ)
	$(RM) $(NAME)

re: fclean all

