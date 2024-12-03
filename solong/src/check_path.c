/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:33:44 by zjamaien          #+#    #+#             */
/*   Updated: 2024/12/04 00:19:04 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static char	**blank_grid(t_game *game)
{
	int		i;
	char	**grid;

	i = 0;
	grid = ft_calloc((game->map.rows + 1), sizeof(char *));
	if (!grid)
		panic(game, MALLOC_ERR);
	while (i < game->map.rows)
	{
		grid[i] = ft_strdup(game->map.map[i]);
		if (!grid[i])
		{
			free_matrix(grid);
			panic(game, MALLOC_ERR);
		}
		i += 1;
	}
	return (grid);
}

static bool	flood_fill(t_map *map, t_point curr, char **sol_grid)
{
	static int		coins;
	static bool		found_exit;

	if (sol_grid[curr.y][curr.x] == WALL)
		return (false);
	else if (sol_grid[curr.y][curr.x] == COLLECTIBLE)
		coins += 1;
	else if (sol_grid[curr.y][curr.x] == EXIT)
		found_exit = true;
	sol_grid[curr.y][curr.x] = WALL;
	flood_fill(map, (t_point){curr.x + 1, curr.y}, sol_grid);
	flood_fill(map, (t_point){curr.x - 1, curr.y}, sol_grid);
	flood_fill(map, (t_point){curr.x, curr.y + 1}, sol_grid);
	flood_fill(map, (t_point){curr.x, curr.y - 1}, sol_grid);
	return (coins = map->collectibles && found_exit);
}

void	check_path(t_game *game)
{
	char	**sol_grid;

	sol_grid = blank_grid(game);
	if (!flood_fill(&game->map, game->map.player_pos, sol_grid))
	{
		free_matrix(sol_grid);
		panic(game, UNACHIEVABLE_ENITES);
	}
	free_matrix(sol_grid);
}
