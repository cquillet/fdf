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

DIRSRC = .
DIROBJ = .

VERSION_GET = $(shell sw_vers | grep "ProductVersion:" | grep -o "[0-9]\+\.[0-9]\+")
SIERRA = 10.12
EL_CAPITAN = 10.11

CC = gcc

DIRLIBS = ../libs
DIRGRAPHLIBS = $(DIRLIBS)

ifeq ($(VERSION_GET), $(SIERRA))
DIRMLX = $(DIRGRAPHLIBS)/minilibx_macos_sierra
else
DIRMLX = $(DIRGRAPHLIBS)/minilibx_macos
endif

DIRLIBFT = $(DIRLIBS)/libft
DIRHEADER = $(DIRLIBFT)/includes $(DIRMLX)
CFLAGS = $(DIRHEADER:%=-I%) -Wall -Wextra -Werror

LDFLAGS = $(DIRLIBS:%=-L%) -framework OpenGL -framework AppKit
LIBNAME = libft.a libmlx.a libm.a
LDLIBS = $(LIBNAME:lib%.a=-l%)

SRC = check_map.c color_map.c draw.c fdf.c fdf_key_event.c fdf_mouse_event.c \
get_map.c isometric.c main.c parsing.c projection.c

OBJ = $(SRC:%.c=%.o)

RM = rm -f

.PHONY: all clean fclean re lib

all: $(NAME)

$(NAME): lib $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@ $(LDLIBS)

lib:
	make -C $(DIRLIBS)

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
