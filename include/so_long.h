/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:38:11 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/23 21:51:23 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef PIXEL
#  define PIXEL 40
# endif

# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

enum
{
	ON_DESTROY = 17,
	ESC_KEY = 65307,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100
};

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_queue
{
	t_point	*points;
	int		front;
	int		rear;
	int		size;
}	t_queue;

typedef struct s_play
{
	int		pos_x;
	int		pos_y;
	int		p_coins;
}	t_play;

typedef struct s_map
{
	char	**map;
	int		rows;
	int		cols;
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*character;
	void	*wall;
	void	*exit;
	void	*floor;
	int		t_coins;
	t_play	*player;
	t_map	*map;
}	t_game;


void	error_exit(const char *msg);
int		file_lines_ber(int fd);

void	init_the_so_long(char *file, int lines);
void	init_map(t_game *game, char *file, int size);
void	free_matriz(char ***matriz);
void	free_matriz_int(int ***matriz, size_t size);
int		key_press(int keycode, t_game *game);

#endif