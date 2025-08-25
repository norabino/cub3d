/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:24:01 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/25 14:44:44 by norabino         ###   ########.fr       */
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
	cub3d->textures.north = NULL;
	cub3d->textures.south = NULL;
	cub3d->textures.west = NULL;
	cub3d->textures.east = NULL;
	cub3d->textures.cub3d = cub3d;
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
	ft_strcpy(cub3d->alpha, "abcdefghijklmnopqrstuvwxyz");
	cub3d->map = NULL;
	i = 0;
	while (i < 256)
	{
		cub3d->keys[i] = 0;
		i++;
	}
	cub3d->last_refresh = 0;
	cub3d->fps_last_time = gettime_ms();
	cub3d->fps_frame_count = 0;
	cub3d->current_fps = 0.0;
	cub3d->delta_time = 0.0;
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
