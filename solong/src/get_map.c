/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:17:06 by zjamaien          #+#    #+#             */
/*   Updated: 2024/12/06 20:42:57 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static bool	valid_extension(char *map_file)
{
	size_t	i;

	i = ft_strlen(map_file) - 4;
	if (ft_strncmp(".ber", &map_file[i], 4) == 0)
		return (true);
	return (false);
}

static void	get_nbr_rwos(char *map_file, t_game *game)
{
	int		counter;
	int		map_fd;
	char	*temp;

	counter = 0;
	map_fd = open(map_file, O_RDONLY);
	if (map_fd == -1)
		panic(game, OPEN_MAP_FILE_ERR);
	temp = get_next_line(map_fd);
	while (temp)
	{
		counter++;
		free(temp);
		temp = get_next_line(map_fd);
	}
	if (counter == 0)
		panic(game, EMPITY_MAP_FILE);
	game->map.rows = counter;
	close(map_fd);
}

static void	get_lines(char *map_file, t_game *game)
{
	int	map_fd;
	int	i;
	char	*temp;

	temp = NULL;
	map_fd = open(map_file, O_RDONLY);
	if (map_fd == -1)
		panic(game, OPEN_MAP_FILE_ERR);
	i = 0;
	while (i < game->map.rows)
	{
		game->map.map[i] = get_next_line(map_fd);
		i++;
	}
	temp = NULL;
	game->map.map[i] = NULL;
	close(map_fd);
	i = 0;
	while (i < game->map.rows )
	{
		temp = game->map.map[i];
		game->map.map[i] = ft_strtrim(game->map.map[i], "\n");
		free(temp);
		if (!game->map.map[i])
			panic(game, MALLOC_ERR);
		i++;
	}
	game->map.columns = ft_strlen(game->map.map[0]);
}

void	get_map(char *map_file, t_game *game)
{
	if (!valid_extension(map_file))
		panic(game, INVALID_MAP_FILE);
	get_nbr_rwos(map_file, game);
	game->map.map = malloc((game->map.rows + 1) * sizeof(char *));
	if (!game->map.map)
		panic(game, MALLOC_ERR);
	get_lines(map_file, game);
}
