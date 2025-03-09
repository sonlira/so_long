# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 17:49:36 by abaldelo          #+#    #+#              #
#    Updated: 2025/03/09 17:58:20 by abaldelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del ejecutable
NAME = so_long

# Compilador y flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilib/minilibx-linux -Ilib/libft
#-g3 -fsanitize=address

# Directorios
SRCDIR = src
OBJDIR = obj
LIBFTDIR = lib/libft
MLXDIR = lib/minilibx-linux

# Archivos fuente y objetos
# $(shell find $(SRCDIR) -name "*.c")
SRCS = src/events.c src/free.c src/init.c src/main.c src/map_utils.c src/map_utils1.c src/map_utils2.c src/map.c\
		src/player.c src/render.c src/shortest_way_utils.c src/shortest_way_utils1.c src/shortest_way.c src/utils.c

OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Librerías
LIBFT = $(LIBFTDIR)/libft.a
MLX = $(MLXDIR)/libmlx.a
LIBS = -L$(MLXDIR) -lmlx -L$(LIBFTDIR) -lft -lXext -lX11 -lXrender -lm -lbsd

# Regla principal
all: $(NAME)

# Crear el directorio de objetos si no existe
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compilar los archivos fuente en objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilar la libft
$(LIBFT):
	make -C $(LIBFTDIR) -s

# Compilar MiniLibX
$(MLX):
	make -C $(MLXDIR) -s

# Enlazar el juego con las librerías
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

# Limpiar archivos intermedios
clean:
	rm -rf $(OBJDIR)
	make -C $(LIBFTDIR) clean
	make -C $(MLXDIR) clean

# Eliminar el ejecutable y objetos
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTDIR) fclean

# Recompilar desde cero
re: fclean all

.PHONY: all clean fclean re
