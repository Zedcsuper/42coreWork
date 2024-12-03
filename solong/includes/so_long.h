/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:44:35 by zjamaien          #+#    #+#             */
/*   Updated: 2024/12/03 20:51:06 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "tiles.h"
# include "keys.h"
# include "error_messages.h"
# include "../mlx/mlx.h"
# include <stdbool.h>
# define OPEN_SPACE '0'
# define WALL '1'
# define EXIT 'E'
# define COLLECTIBLE 'C'
# define PLAYER 'P'
# define KEYPRESS_EVENT 2
# define DESTROY_NOTIFY_EVENT 17
# define WIN_MSG "You won!\n"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;
typedef struct s_map
{
	char	**map;
	int		rows;
	int		columns;
	int		collectibles;
	int		exit;
	int		player;
	t_point	player_pos;
}	t_map;
typedef struct s_tiles
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*collectible;
	void	*exit;
}	t_tiles;
typedef struct s_game
{
	t_map	map;
	void	*mlx_ptr;
	void	*win_ptr;
	t_tiles	tiles;
	int		moves;
}	t_game;

/*this function should not be here*/
static inline t_game	init_game(void)
{
	return ((t_game){
		.map.map = NULL,
		.map.rows = 0,
		.map.columns = 0,
		.map.collectibles = 0,
		.map.exit = 0,
		.map.player = 0,
		.tiles.collectible = NULL,
		.tiles.exit = NULL,
		.tiles.floor = NULL,
		.tiles.player = NULL,
		.tiles.wall = NULL,
		.moves = -1,
	});
}

/*parses and save the given map*/
void	get_map(char *map_file, t_game *game);
void	check_path(t_game *game);
void	map_check(t_game *game);
void	init_mlx(t_game *game);
void	render_map(t_game *game);
void	update_player_pos(t_game *game, bool horisontal, int length);
void	put_player_tile(t_game *game);
void	hook_n_run(t_game *game);
int		quit_game(t_game *game);
/*utils*/
void	panic(t_game *game, char *error_msg);
void	destroy(t_game *game);
void	free_matrix(char **matrix);
bool	is_onstr(const char *str, int ch);

#endif
