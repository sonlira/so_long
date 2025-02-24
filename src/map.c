/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:19 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/24 19:07:07 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*==================================*/
void	is_rectangular(t_map *map)
{
	int	row;

	row = 1;
	while (map->map[row])
	{
		if ((int)ft_strlen(map->map[row]) != map->cols)
		{
			free_matriz(&map->map);
			error_exit("Map is not valid, not is rectangular");
		}
		row++;
	}
}
/*==================================*/

/*==================================*/
static int	check_up_do(char *row)
{
	int	col;

	col = 0;
	while (row[col])
	{
		if (row[col] != '1')
			return (0);
		col++;
	}
	return (1);
}

void	is_surrounded_by_one(t_map *map, int lines)
{
	int	last;
	int	row;

	last = map->cols - 1;
	row = 0;
	if (check_up_do(map->map[0]) == 0 || check_up_do(map->map[lines - 1]) == 0)
	{
		free_matriz(&map->map);
		error_exit("The map must be surrounded by '1'");
	}
	while (row < lines)
	{
		if (!(map->map[row][0] == '1' && map->map[row][last] == '1'))
		{
			free_matriz(&map->map);
			error_exit("The map must be surrounded by '1'");
		}
		row++;
	}
}
/*==================================*/

/*==================================*/
static int	count_item(char *row, char item)
{
	int	col;
	int	count;

	col = 0;
	count = 0;
	while (row[col])
	{
		if (row[col] == '0')
		{
			col++;
			continue ;
		}
		else if (row[col] == item)
			count++;
		col++;
	}
	return (count);
}

void	check_items(t_game *game, int lines)
{
	int	c_count;
	int	p_count;
	int	e_count;
	int	row;

	c_count = 0;
	e_count = 0;
	p_count = 0;
	row = 1;
	while (row < lines - 1)
	{
		c_count += count_item(game->map->map[row], 'C');
		p_count += count_item(game->map->map[row], 'P');
		e_count += count_item(game->map->map[row], 'E');
		row++;
	}
	if (p_count != 1 || e_count != 1 || c_count < 1)
	{
		free_matriz(&game->map->map);
		error_exit("Number of invalid items");
	}
	game->t_coins = c_count;
}
/*==================================*/

/*==================================*/
void	check_valid_items(t_map *map)
{
	int	row;
	int	col;

	row = 1;
	while (row < map->rows -1)
	{
		col = 0;
		while (map->map[row][col])
		{
			if (map->map[row][col] == '0')
			{
				col++;
				continue ;
			}
			else if (!ft_strchr("1PEC", map->map[row][col]))
			{
				free_matriz(&map->map);
				error_exit("Item not valid");
			}
			col++;
		}
		row++;
	}
}
/*==================================*/
/*==================================*/
static void get_pocision_of_p(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->map->rows)
	{
		col = 0;
		while (col < game->map->cols)
		{
			if (game->map->map[row][col] == 'P')
			{
				game->player->pos_x = row;
				game->player->pos_y = col;
				row = game->map->rows;
				break ;
			}
			col++;
		}
		row++;
	}
}

static	int **create_a_map_copy(t_map *map)
{
	int	**matriz;
	int	row;

	matriz = ft_calloc(map->rows + 1, sizeof(int *));
	if (!matriz)
		return (NULL);
	row = 0;
	while (row < map->rows)
	{
		matriz[row] = ft_calloc(map->cols + 1, sizeof(int));
		if (!matriz[row])
			return (free_matriz_int(&matriz, map->rows), NULL);
		row++;
	}
	return (matriz);
}
/*-------------------------*/



t_queue *create_queue(int size)
{
	t_queue *q;

	q = malloc(sizeof(t_queue));
	if (!q)
		return (NULL);
	q->points = malloc(sizeof(t_point) * size);
	if (!q->points)
		return (free(q), NULL);
	q->front = 0;
	q->final = 0;
	q->c_coins = 0;
	q->with_exit = 0;
	q->size = size;
	return (q);
}

void enqueue(t_queue *q, int row, int col)
{
	if (q->final == q->size)
		return ;
	q->points[q->final].row = row;
	q->points[q->final].col = col;
	q->final++;
}

t_point dequeue(t_queue *q)
{
	t_point p;

	p.col = -1;
	p.row = -1;
	if (q->front == q->final)
		return (p);
	p = q->points[q->front];
	q->front++;
	return (p);
}
/*-------------------------*/
/*-------bfs------------------*/
void get_moves(int moves[4][2])
{
	moves[0][0] = -1;
	moves[0][1] = 0;
	moves[1][0] = 1;
	moves[1][1] = 0;
	moves[2][0] = 0;
	moves[2][1] = -1;
	moves[3][0] = 0;
	moves[3][1] = 1;
}
int is_valid_pos(t_map *map, int **visited, int nr, int nc)
{
	if ((nr < 0 && nr >= map->rows) || (nc < 0 && nc >= map->cols))
		return (0);
	if (visited[nr][nc] == 1)
		return (0);
	if (map->map[nr][nc] == '1')
		return (0);
	return (1);
}

void	apply_the_movements(t_map *map, int **v, t_queue *q, int m[4][2], t_point c)
{
	int	i;
	int new_row;
	int new_col;

	i = 0;
	while (i < 4)
	{
		new_row = c.row + m[i][0];
		new_col = c.col + m[i][1];
		if (is_valid_pos(map, v, new_row, new_col))
		{
			if (map->map[new_row][new_col] == 'C')
				q->c_coins++;
			if (map->map[new_row][new_col] == 'E')
				q->with_exit = 1;
			v[new_row][new_col] = 1;
			enqueue(q, new_row, new_col);
		}
		i++;
	}
}
int find_coins(t_game *game, int **visited, t_queue *q)
{
	t_point current;
	int	moves[4][2];

	enqueue(q, game->player->pos_x, game->player->pos_y);
	get_moves(moves);
	(void)visited;
	while (q->front != q->final)
	{
		current = dequeue(q);
		apply_the_movements(game->map, visited, q, moves, current);
	}
	if (q->c_coins != game->t_coins || q->with_exit != 1)
		return (0);
	return (1);
}


/*-------------------------*/

void	check_accessibility(t_game *game)
{
	int		**visited;
	t_queue	*q;

	get_pocision_of_p(game);
	visited = create_a_map_copy(game->map);
	if (!visited)
		error_exit("An error occurred while checking the map access");
	visited[game->player->pos_x][game->player->pos_y] = 1;
	q = create_queue(game->map->rows * game->map->cols);
	if (!q)
		error_exit("An error occurred while checking the map access");
	if (find_coins(game, visited, q) == 0)
	{
		free_queue(q);
		free_matriz_int(&visited, game->map->rows);
		error_exit("Unaccessible exit or collectibles");
	}
	free_matriz_int(&visited, game->map->rows);
}

/*==================================*/
/*==================================*/
static void	clean_map(t_map *map, int lines)
{
	int		row;
	char	*line;

	row = 0;
	while (row < lines -1)
	{
		line = ft_strrchr(map->map[row], '\n');
		if (line)
			line[0] = '\0';
		row++;
	}
}

void	init_map(t_game *game, char *file, int lines)
{
	int	i;
	int	fd;

	fd = open(file, O_RDONLY);
	free(file);
	if (fd == -1)
		error_exit("Error opening the file");
	game->map->map = ft_calloc(lines + 1, sizeof(char *));
	if (!game->map)
		error_exit("Failed to reserve memory for map");
	i = 0;
	while (i < lines)
	{
		game->map->map[i] = get_next_line(fd);
		if (!game->map->map[i])
		{
			free_matriz(&game->map->map);
			error_exit("Failed to reserve memory for map");
		}
		i++;
	}
	close(fd);
	clean_map(game->map, lines);
	game->map->rows = lines;
	game->map->cols = ft_strlen(game->map->map[0]);
	is_rectangular(game->map);
	is_surrounded_by_one(game->map, lines);
	check_items(game, lines);
	check_valid_items(game->map);
	check_accessibility(game);
}
/*==================================*/