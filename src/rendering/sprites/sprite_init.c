/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/18 18:06:33 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/* Initialize sprite system */
void	init_sprites(t_cub3d *cub3d)
{
	int	i;

	cub3d->sprites = NULL;
	cub3d->sprite_count = 0;
	cub3d->depth_buffer.width = SCREEN_WIDTH;
	cub3d->depth_buffer.buffer = malloc(sizeof(double) * SCREEN_WIDTH);
	if (!cub3d->depth_buffer.buffer)
		exit_error("Failed to allocate depth_buffer", cub3d);
	i = 0;
	while (i < SCREEN_WIDTH)
		cub3d->depth_buffer.buffer[i++] = 999999;
}

/* Free sprite resources */
void	free_sprites(t_cub3d *cub3d)
{
	if (!cub3d)
		return ;
	if (cub3d->sprites)
	{
		free(cub3d->sprites);
		cub3d->sprites = NULL;
	}
	cub3d->sprite_count = 0;
	if (cub3d->depth_buffer.buffer)
	{
		free(cub3d->depth_buffer.buffer);
		cub3d->depth_buffer.buffer = NULL;
	}
}
