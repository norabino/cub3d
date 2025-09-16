/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:25:18 by norabino          #+#    #+#             */
/*   Updated: 2025/09/16 01:29:49 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdint.h>

void	free_portal_paths(t_cub3d *cub3d)
{
	int	i;

	if (cub3d->prtl_sprites.path)
	{
		i = 0;
		while (i < 16 && cub3d->prtl_sprites.path[i])
		{
			free(cub3d->prtl_sprites.path[i]);
			cub3d->prtl_sprites.path[i] = NULL;
			i++;
		}
		free(cub3d->prtl_sprites.path);
		cub3d->prtl_sprites.path = NULL;
	}
	cub3d->prtl_sprites.frame_counter = 0;
	cub3d->prtl_sprites.current_frame = 0;
	if (cub3d->tp_portals)
	{
		free(cub3d->tp_portals);
		cub3d->tp_portals = NULL;
	}
}

/* Met à jour les animations des portails */
void	update_portal_animations(t_cub3d *cub3d)
{
	int		i;
	long	current_time;
	long	frame_duration;

	if (!cub3d || !cub3d->tp_portals || cub3d->nb_portals <= 0)
		return ;
	current_time = gettime_ms();
	frame_duration = 1000 / FPS;
	i = 0;
	while (i < cub3d->nb_portals)
	{
		if ((current_time - cub3d->prtl_sprites.last_frame_time)
			>= frame_duration)
		{
			cub3d->prtl_sprites.current_frame
				= (cub3d->prtl_sprites.current_frame + 1) % 16;
			cub3d->prtl_sprites.last_frame_time = current_time;
			cub3d->prtl_sprites.frame_counter++;
		}
		i++;
	}
}

void	free_portal_sprites(t_cub3d *cub3d)
{
	int	i;

	if (!cub3d)
		return ;
	if (cub3d->prtl_sprites.frames)
	{
		i = 0;
		while (i < 16)
		{
			if (cub3d->prtl_sprites.frames[i].img && cub3d->mlx.mlx
				&& cub3d->mlx.win)
			{
				mlx_destroy_image(cub3d->mlx.mlx,
					cub3d->prtl_sprites.frames[i].img);
				cub3d->prtl_sprites.frames[i].img = NULL;
				cub3d->prtl_sprites.frames[i].addr = NULL;
			}
			i++;
		}
		free(cub3d->prtl_sprites.frames);
		cub3d->prtl_sprites.frames = NULL;
	}
	free_portal_paths(cub3d);
}
