# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/28 07:55:52 by abaldelo          #+#    #+#              #
#    Updated: 2025/02/20 17:51:13 by abaldelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
RM		= rm -f
CC		= cc
CCFLAGS = -Wall -Werror -Wextra
LIB		= ar r
SRC		= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c\
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c\
		ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c\
		ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c\
		ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c ft_strjoin.c\
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c\
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c get_next_line.c

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC)
		@$(CC) $(CCFLAGS) $(SRC) -c
		@$(LIB) $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME) $(OBJ)

re: clean fclean all

.PHONY: all fclean clean re