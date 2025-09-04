/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:24:01 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/04 15:55:43 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_basic_values(t_cub3d *cub3d)
{
	cub3d->mlx.mlx = NULL;
	cub3d->mlx.img = NULL;
	cub3d->mlx.win = NULL;
	cub3d->player.direction = 0;
	cub3d->player.cub3d = cub3d;
	cub3d->player.last_prtl_pos.x = -1;
	cub3d->player.last_prtl_pos.y = -1;
	cub3d->textures.north = NULL;
	cub3d->textures.south = NULL;
	cub3d->textures.west = NULL;
	cub3d->textures.east = NULL;
	cub3d->textures.floor = NULL;
	cub3d->textures.ceiling = NULL;
	cub3d->textures.north_img.img = NULL;
	cub3d->textures.south_img.img = NULL;
	cub3d->textures.west_img.img = NULL;
	cub3d->textures.east_img.img = NULL;
	cub3d->textures.floor_img.img = NULL;
	cub3d->textures.ceiling_img.img = NULL;
	cub3d->textures.cub3d = cub3d;
	cub3d->nb_portals = 0;
}

static void	init_time_and_fps(t_cub3d *cub3d)
{
	cub3d->last_refresh = 0;
	cub3d->fps_last_time = 0;
	cub3d->fps_frame_count = 0;
	cub3d->current_fps = 0.0;
	cub3d->delta_time = 0.0;
	cub3d->mouse_x = SCREEN_WIDTH / 2;
	cub3d->mouse_y = SCREEN_HEIGHT / 2;
	cub3d->mouse_last_x = SCREEN_WIDTH / 2;
	cub3d->mouse_captured = 0;
}

static void	init_colors_and_input(t_cub3d *cub3d)
{
	cub3d->colors.floor[0] = -1;
	cub3d->colors.floor[1] = -1;
	cub3d->colors.floor[2] = -1;
	cub3d->colors.ceiling[0] = -1;
	cub3d->colors.ceiling[1] = -1;
	cub3d->colors.ceiling[2] = -1;
	cub3d->colors.cub3d = cub3d;
	cub3d->player.fov = 0;
	ft_bzero(cub3d->portals, 26);
	cub3d->tp_portals = NULL;
	cub3d->map = NULL;
	ft_bzero(cub3d->keys, 256);
	init_time_and_fps(cub3d);
}

void	init_game_state(t_cub3d *cub3d)
{
	init_basic_values(cub3d);
	init_colors_and_input(cub3d);
}
