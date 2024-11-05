/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:55:38 by zjamaien          #+#    #+#             */
/*   Updated: 2024/11/04 23:24:12 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_H
# define ERROR_MESSAGES_H

# define MALLOC_ERR "malloc() failed"
# define MLX_INIT_ERR "Failed to initialize mlx"
# define MLX_NEW_WINDOW_ERR "Failed to open a new window"
/*CL arguments Validation*/
# define INVALID_NBR__ARGS "Invalid number of arguments"
# define NULL_MAP "NULL map arguments"
/*map validation*/
# define INVALID_ENTITY "Invalid entity on map's file"
# define INVALID_FORMAT "Invalid map"
# define MAP_NOT_CLOSED "Map is not closed by walls"
# define INVALID_NBR_EXIT "Invalid number of exit (E)"
# define NO_COLLECTIBLES "Map Dose not have fish (C)"
# define INVALID_NBR_PLAYERS "Ivalid number of start pos (P)"
# define UNACHIEVABLE_ENITES "Map has unachievable entities"
/* reading maps content*/
# define INVALID_MAP_FILE "Invalid map file extension"
# define OPEN_MAP_FILE_ERR "Failed open map file"
# define EMPITY_MAP_FILE "Mapo file is empty"
/*xpm opening*/
# define WALL_XPM_ERR "Failed to open wall image"
# define FLOOR_XPM_ERR "failed to open floor image"
# define COLLECTIBLE_XPM_ERR "Failed to open collectible image"
# define EXIT_XPM_ERR "Failed to open exit image"
# define PLAYER_XPM_ERR "Falied to open player image"
/*from file map_check.c*/
# define VALID_ENTITIES "ECPP01"

#endif
