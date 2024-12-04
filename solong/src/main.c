/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:33:14 by zjamaien          #+#    #+#             */
/*   Updated: 2024/12/04 22:29:26 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
//hi
static void	args_check(int argc, char **argv)
{
	if (argc != 2)
		panic(NULL,  INVALID_NBR__ARGS);
	if (*argv[1] == '\0')
		panic(NULL, NULL_MAP);
}

int	main(int argc, char **argv)
{
	t_game	game;

	args_check(argc, argv);
	game = init_game();
	get_map(argv[1], &game);
	map_check(&game);
	init_mlx(&game);
	render_map(&game);
	hook_n_run(&game);
	return (EXIT_SUCCESS);
}
