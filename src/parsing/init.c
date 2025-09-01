/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:24:01 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/01 19:15:47 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Initializes basic values of the main structure
** Like preparing a toolbox by resetting
** all compartments to zero before starting
*/
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

/*
** Initialise les paramètres de la souris et du temps
** Comme régler l'horloge et la souris d'un ordinateur
** avant de commencer à l'utiliser
*/
static void	init_mouse_and_time(t_cub3d *cub3d)
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

/*
** Initializes colors and keyboard keys
** Like setting default colors on a TV
** and clearing the memory of pressed keys
*/
static void	init_colors_and_keys(t_cub3d *cub3d)
{
	int	i;

	cub3d->colors.floor[0] = -1;
	cub3d->colors.floor[1] = -1;
	cub3d->colors.floor[2] = -1;
	cub3d->colors.ceiling[0] = -1;
	cub3d->colors.ceiling[1] = -1;
	cub3d->colors.ceiling[2] = -1;
	cub3d->colors.cub3d = cub3d;
	cub3d->player.fov = 0;
	i = 0;
	while (i < 26)
	{
		cub3d->portals[i] = 0;
		i++;
	}
	cub3d->tp_portals = NULL;
	cub3d->map = NULL;
	i = 0;
	while (i < 256)
	{
		cub3d->keys[i] = 0;
		i++;
	}
	init_mouse_and_time(cub3d);
}

/*
** Main initialization function
** Like fully preparing a new car before first startup
** making sure everything is zeroed and ready to work
*/
void	init(t_cub3d *cub3d)
{
	init_basic_values(cub3d);
	init_colors_and_keys(cub3d);
}
