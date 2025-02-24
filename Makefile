# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 17:49:36 by abaldelo          #+#    #+#              #
#    Updated: 2025/02/24 18:39:40 by abaldelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del ejecutable
NAME = so_long

# Compilador y flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address -Iinclude -Ilib/minilibx-linux -Ilib/libft

# Directorios
SRCDIR = src
OBJDIR = obj
LIBFTDIR = lib/libft
MLXDIR = lib/minilibx-linux

# Archivos fuente y objetos
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Librerías
LIBFT = $(LIBFTDIR)/libft.a
MLX = $(MLXDIR)/libmlx.a
LIBS = -L$(MLXDIR) -lmlx -L$(LIBFTDIR) -lft -lXext -lX11 -lm -lbsd

# Regla principal
all: $(NAME)

# Compilar los archivos fuente en objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilar la libft
$(LIBFT):
	make -C $(LIBFTDIR)

# Compilar MiniLibX
$(MLX):
	make -C $(MLXDIR)

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
