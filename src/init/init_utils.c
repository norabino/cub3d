/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:00:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/18 18:31:56 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_mouse(t_cub3d *cub3d)
{
	cub3d->mouse.x = SCREEN_WIDTH / 2;
	cub3d->mouse.y = SCREEN_HEIGHT / 2;
	cub3d->mouse.last_x = SCREEN_WIDTH / 2;
	cub3d->mouse.captured = 0;
}

void	init_time(t_cub3d *cub3d)
{
	cub3d->time.last_refresh = 0;
	cub3d->time.fps_last_time = 0;
	cub3d->time.fps_frame_count = 0;
	cub3d->time.current_fps = 0.0;
	cub3d->time.delta_time = 0.0;
}

void	init_colors(t_cub3d *cub3d)
{
	cub3d->colors.floor[0] = -1;
	cub3d->colors.floor[1] = -1;
	cub3d->colors.floor[2] = -1;
	cub3d->colors.ceiling[0] = -1;
	cub3d->colors.ceiling[1] = -1;
	cub3d->colors.ceiling[2] = -1;
}

void	init_view(t_cub3d *cub3d)
{
	cub3d->view.plane_x = -1;
	cub3d->view.plane_y = -1;
}

