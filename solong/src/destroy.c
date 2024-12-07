/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:09:52 by zjamaien          #+#    #+#             */
/*   Updated: 2024/12/06 20:12:54 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	destroy_tiles(t_game *game)
{
	if (game->tiles.wall)
	{
		mlx_destroy_image(game->mlx_ptr, game->tiles.wall);
		game->tiles.wall = NULL;
	}
	if (game->tiles.floor)
	{
		mlx_destroy_image(game->mlx_ptr, game->tiles.floor);
		game->tiles.floor = NULL;
	}
	if (game->tiles.player)
	{
		mlx_destroy_image(game->mlx_ptr, game->tiles.player);
		game->tiles.player = NULL;
	}
	if (game->tiles.collectible)
	{
		mlx_destroy_image(game->mlx_ptr, game->tiles.collectible);
		game->tiles.collectible = NULL;
	}
	if (game->tiles.exit)
	{
		mlx_destroy_image(game->mlx_ptr, game->tiles.exit);
		game->tiles.exit = NULL;
	}
}

void	destroy(t_game *game)
{
	if (!game)
		return ;
	destroy_tiles(game);
	if (game->win_ptr)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		game->win_ptr = NULL;
	}
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		game->mlx_ptr = NULL;
	}
	if (game->map.map)
	{
		free_matrix(game->map.map);
		game->map.map = NULL;
	}
}

void	free_matrix(char **matrix)
{
	size_t	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
