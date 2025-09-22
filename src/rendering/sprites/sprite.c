/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/22 16:24:19 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	update_depth_buffer(t_cub3d *cub3d, int x, double distance)
{
	if (x >= 0 && x < SCREEN_WIDTH && distance < cub3d->depth_buffer.buffer[x])
		cub3d->depth_buffer.buffer[x] = distance;
}

void	render_sprites(t_cub3d *cub3d)
{
	int				i;
	t_sprite_calc	calc;

	if (!cub3d->prtl_sprites.frames || cub3d->prtl_sprites.frame_counter <= 0)
		return ;
	collect_portal_sprites(cub3d);
	if (!cub3d->sprites || cub3d->sprite_count <= 0)
		return ;
	sort_sprites_by_distance(cub3d);
	i = 0;
	while (i < cub3d->sprite_count)
	{
		calc_sprite_properties(cub3d, &cub3d->sprites[i], &calc);
		calc_sprite_screen_bounds(&calc);
		draw_sprite_pixels(cub3d, &cub3d->sprites[i], &calc);
		i++;
	}
}
