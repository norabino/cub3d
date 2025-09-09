/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:25:18 by norabino          #+#    #+#             */
/*   Updated: 2025/09/09 20:16:05 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

/* Libère la mémoire des sprites de portails */
void	free_portal_sprites(t_cub3d *cub3d)
{
	int	i;
	int	j;

	if (!cub3d || !cub3d->tp_portals || cub3d->nb_portals <= 0)
		return ;
	i = 0;
	while (i < cub3d->nb_portals)
	{
		if (cub3d->prtl_sprites.frames)
		{
			j = 0;
			while (j < 16)
			{
				if (cub3d->prtl_sprites.frames[j].img && cub3d->mlx.mlx)
					mlx_destroy_image(cub3d->mlx.mlx,
						cub3d->prtl_sprites.frames[j].img);
				j++;
			}
			free(cub3d->prtl_sprites.frames);
		}
		i++;
	}
	free(cub3d->tp_portals);
	cub3d->tp_portals = NULL;
}
