/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:18:06 by zjamaien          #+#    #+#             */
/*   Updated: 2024/11/04 20:17:03 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	throw_error_if(t_game *game)
{
	if (game->map.exit == 0 || game->map.exit > 1)
		panic(game, INVALID_NBR_EXIT);
	if (game->map.collectibles == 0)
		panic(game, NO_COLLECTIBLES);
	if (game->map.player == 0 || game->map.player > 1)
		panic(game, INVALID_NBR_PLAYERS);
}

static void	check_elemnts(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map.rows)
	{
		j = -1;
		while (++j < game->map.columns)
		{
			if (!is_onstr(VALID_ENTITIES, game->map.map[i][j]))
				panic(game, INVALID_ENTITY);
			if (game->map.map[i][j] == EXIT)
				game->map.exit += 1;
			else if (game->map.map[i][j] == COLLECTIBLE)
				game->map.collectibles += 1;
			else if (game->map.map[i][j] == PLAYER)
			{
				game->map.player += 1;
				game->map.player_pos = (t_point){j, i};
			}
		}
	}
	throw_error_if(game);
}

static bool	is_closed(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->rows)
		if (map->map[i][0] != WALL || map->map[i][map->columns - 1] != WALL)
			return (false);
	i = -1;
	while (++i < map->columns)
		if (map->map[0][i] != WALL || map->map[map->rows - 1][i] != WALL)
			return (false);
	return (true);
}

static bool	valid_form(t_game *game)
{
	size_t	len;
	size_t	i;

	len = game->map.columns;
	i = 0;
	while (game->map.map[i] != NULL)
	{
		if (len != ft_strlen(game->map.map[i]))
			return (false);
		i += 1;
	}
	return (true);
}

void	map_check(t_game *game)
{
	if (!valid_form(game))
		panic(game, INVALID_FORMAT);
	check_elemnts(game);
	if (!is_closed(&game->map))
		panic(game, MAP_NOT_CLOSED);
	check_path(game);
}
