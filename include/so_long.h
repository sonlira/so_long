/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:38:11 by abaldelo          #+#    #+#             */
/*   Updated: 2025/03/09 18:05:34 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef PX
#  define PX 65
# endif

# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>

enum
{
	ON_DESTROY	= 17,
	ESC_KEY		= 65307,
	KEY_W		= 119,
	KEY_A		= 97,
	KEY_S		= 115,
	KEY_D		= 100,
	MOVES		= 4,
	WALL		= '1',
	FLOOR		= '0',
	PLAYER		= 'P',
	COIN		= 'C',
	EXIT		= 'E',
};
typedef struct s_point
{
	int	row;
	int	col;
}	t_point;

typedef struct s_rute
{
	t_point	rc;
	int		cost;
}	t_rute;

typedef struct s_queue
{
	t_point	*points;
	int		front;
	int		final;
	int		size;
	int		c_coins;
	int		with_exit;
}	t_queue;

typedef struct s_play
{
	int		row;
	int		col;
	int		p_coins;
	int		p_moves;
}	t_play;

typedef struct s_map
{
	char	**map;
	int		rows;
	int		cols;
	t_point	moves[4];
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*p;
	void	*w;
	void	*e;
	void	*f;
	void	*c;
	int		t_coins;
	int		max_moves;
	t_play	*player;
	t_map	*map;
	t_point	*locations;
	t_point	p_exit;
	t_rute	*rute;
}	t_game;

// init.c
void	init_the_so_long(char *file, int lines);
// map.c
void	init_map(t_game *game, char *file, int size);
// map_utils.C
int		**start_matriz_int(t_map *map, int number);
void	create_map(t_game *game, char *file, int lines);
void	check_rectangular_shape(t_map *map);
// map_utils1.C
void	check_one_on_edges(t_map *map, int lines);
void	check_items(t_game *game, int lines);
void	check_valid_items(t_map *map);
// map_utils2.C
void	check_accessibility(t_game *game);
// shortest_way.c
int		find_the_shortest_way(t_game *game);
int		distance_bfs(t_game *game, t_point start, t_point end);
// shortest_way_utils.c
int		get_pocisions_of_items(t_game *game);
int		**init_costs(t_game *game);
// shortest_way_utils1.c
int		best_pick_up_order(t_game *game);
// render.c
void	draw_map(t_game *game);
// player.c
int		update_pos_player(t_game *game, t_point new);
// events.c
int		close_window(t_game *game);
int		key_press(int keycode, t_game *game);
// utils.c
void	error_exit(const char *msg);
int		file_lines_ber(int fd);
t_queue	*create_queue(int size);
void	enqueue(t_queue *queue, int row, int col);
t_point	dequeue(t_queue *queue);
// free.c
void	free_matriz(char ***matriz);
void	free_matriz_int(int ***matriz, size_t size);
void	free_matriz_point(t_point ***matriz, size_t size);
void	free_queue(t_queue *q);
void	free_mlx(t_game *game);

#endif