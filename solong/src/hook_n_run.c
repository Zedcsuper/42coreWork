/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_n_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:50:31 by zjamaien          #+#    #+#             */
/*   Updated: 2024/11/04 23:32:53 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	quit_game(t_game *game)
{
	destroy(game);
	exit(EXIT_SUCCESS);
}

int	on_press(int key, t_game *game)
{
	if (key == ESC)
		quit_game(game);
	else if (key == W || key == UP)
		update_player_pos(game, false, -1);
	else if (key == A || key == LEFT)
		update_player_pos(game, true, -1);
	else if (key == S || key == DOWN)
		update_player_pos(game, false, 1);
	else if (key == D || key == RIGHT)
		update_player_pos(game, true, 1);
	return (EXIT_SUCCESS);
}

void	hook_n_run(t_game *game)
{
	mlx_hook(game->win_ptr, KEYPRESS_EVENT, (1L << 0), on_press, game);
	mlx_hook(game->win_ptr, DESTROY_NOTIFY_EVENT, (1L << 17),
		quit_game, game);
	mlx_loop(game->mlx_ptr);
}
