/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:27:59 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/18 18:30:25 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_depth_buffer(t_cub3d *cub3d)
{
	int	i;

	cub3d->depth_buffer.buffer = malloc(sizeof(double) * SCREEN_WIDTH);
	if (!cub3d->depth_buffer.buffer)
		exit_error("Failed to allocate depth buffer", cub3d);
	i = 0;
	while (i < SCREEN_WIDTH)
		cub3d->depth_buffer.buffer[i++] = 999999.0;
}

void	init_sprites(t_cub3d *cub3d)
{
	cub3d->sprites = NULL;
	cub3d->sprite_count = 0;
	cub3d->depth_buffer.width = SCREEN_WIDTH;
	init_depth_buffer(cub3d);
}
