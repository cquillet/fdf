# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/09 16:13:19 by cquillet          #+#    #+#              #
#    Updated: 2018/02/06 15:43:06 by cquillet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

DIRSRC = .
DIROBJ = .

VERSION_GET = $(shell sw_vers | grep "ProductVersion:" | grep -o "[0-9]\+\.[0-9]\+")
SIERRA = 10.12
EL_CAPITAN = 10.11

ifeq ($(VERSION_GET), $(SIERRA))
DIRMLX = minilibx_macos_sierra
else
DIRMLX = minilibx_macos
endif

DIRHEADER = ./libft/includes ./$(DIRMLX)

DIRLIB = ./libft ./$(DIRMLX)

CC = gcc

CFLAGS = $(DIRHEADER:%=-I%) -Wall -Wextra -Werror

LDFLAGS = $(DIRLIB:%=-L%) -framework OpenGL -framework AppKit
LIBNAME = libft.a libmlx.a libm.a
LDLIBS = $(LIBNAME:lib%.a=-l%)

SRC = check_map.c color_map.c draw.c fdf.c fdf_key_event.c fdf_mouse_event.c \
get_map.c isometric.c main.c parsing.c projection.c

OBJ = $(SRC:%.c=%.o)

RM = rm -f

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	make -C $(DIRMLX)
	$(CC) $(LDFLAGS) $? -o $@ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $? -o $@

clean:
	make -C libft clean
	make -C $(DIRMLX) clean
	$(RM) $(OBJ)

fclean:
	make -C libft fclean
	make -C $(DIRMLX) clean
	$(RM) $(OBJ)
	$(RM) $(NAME)

re: fclean all
