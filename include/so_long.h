/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:38:11 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/18 22:50:40 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef PIXEL
#  define PIXEL 40
# endif

# include "mlx.h"
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

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img;
	int		img_x;
	int		img_y;
	char	*map[5];
}	t_game;

int	key_press(int keycode, t_game *game);

#endif