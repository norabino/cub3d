/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/16 15:50:02 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/* Initialize z-buffer for depth testing */
void	init_zbuffer(t_cub3d *cub3d)
{
	int	i;

	cub3d->zbuffer.width = SCREEN_WIDTH;
	cub3d->zbuffer.buffer = malloc(sizeof(double) * SCREEN_WIDTH);
	if (!cub3d->zbuffer.buffer)
		exit_error("Failed to allocate z-buffer", cub3d);
	i = 0;
	while (i < SCREEN_WIDTH)
	{
		cub3d->zbuffer.buffer[i] = __DBL_MAX__;
		i++;
	}
}

/* Initialize sprite system */
void	init_sprites(t_cub3d *cub3d)
{
	cub3d->sprites = NULL;
	cub3d->sprite_count = 0;
	init_zbuffer(cub3d);
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
	if (cub3d->zbuffer.buffer)
	{
		free(cub3d->zbuffer.buffer);
		cub3d->zbuffer.buffer = NULL;
	}
}
