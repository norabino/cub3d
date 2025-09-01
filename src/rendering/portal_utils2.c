/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:25:18 by norabino          #+#    #+#             */
/*   Updated: 2025/09/01 20:40:54 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	update_portal_animations(t_cub3d *cub3d)
{
	int		i;
	long	current_time;
	long	frame_duration;

	current_time = gettime_ms();
	frame_duration = 1000 / 60;
	i = 0;
	while (i < cub3d->nb_portals)
	{
		if ((current_time - cub3d->tp_portals[i].sprite.last_frame_time)
			>= frame_duration)
		{
			cub3d->tp_portals[i].sprite.current_frame
				= (cub3d->tp_portals[i].sprite.current_frame + 1) % 8;
			cub3d->tp_portals[i].sprite.last_frame_time = current_time;
			cub3d->tp_portals[i].sprite.frame_counter++;
		}
		i++;
	}
}

void	free_portal_sprites(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub3d->nb_portals)
	{
		j = 0;
		while (j < 4)
		{
			if (cub3d->tp_portals[i].sprite.frames[j].img)
				mlx_destroy_image(cub3d->mlx.mlx,
					cub3d->tp_portals[i].sprite.frames[j].img);
			j++;
		}
		i++;
	}
}
