/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/16 16:17:14 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/* Main sprite rendering function */
void	render_sprites(t_cub3d *cub3d)
{
	int				i;
	t_sprite_calc	calc;

	if (!cub3d)
		return ;
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
