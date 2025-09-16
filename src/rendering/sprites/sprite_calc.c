/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/16 16:17:14 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/* Calculate sprite transformation and screen position */
void	calc_sprite_properties(t_cub3d *cub3d, t_sprite *sprite,
	t_sprite_calc *calc)
{
	calc->sprite_x = sprite->x - cub3d->player.pos_x;
	calc->sprite_y = sprite->y - cub3d->player.pos_y;
	calc->inv_det = 1.0 / (cub3d->view.plane_x * cub3d->player.dir_y
			- cub3d->player.dir_x * cub3d->view.plane_y);
	calc->transform_x = calc->inv_det * (cub3d->player.dir_y * calc->sprite_x
			- cub3d->player.dir_x * calc->sprite_y);
	calc->transform_y = calc->inv_det * (-cub3d->view.plane_y * calc->sprite_x
			+ cub3d->view.plane_x * calc->sprite_y);
	calc->sprite_screen_x = (int)((SCREEN_WIDTH / 2)
			* (1 + calc->transform_x / calc->transform_y));
	calc->sprite_height = ft_abs((int)(SCREEN_HEIGHT / calc->transform_y
				* 0.75));
	calc->sprite_width = calc->sprite_height;
}

/* Calculate sprite screen drawing bounds with clipping */
void	calc_sprite_screen_bounds(t_sprite_calc *calc)
{
	calc->draw_start_y = -calc->sprite_height / 2 + SCREEN_HEIGHT / 2;
	if (calc->draw_start_y < 0)
		calc->draw_start_y = 0;
	calc->draw_end_y = calc->sprite_height / 2 + SCREEN_HEIGHT / 2;
	if (calc->draw_end_y >= SCREEN_HEIGHT)
		calc->draw_end_y = SCREEN_HEIGHT - 1;
	calc->draw_start_x = -calc->sprite_width / 2 + calc->sprite_screen_x;
	if (calc->draw_start_x < 0)
		calc->draw_start_x = 0;
	calc->draw_end_x = calc->sprite_width / 2 + calc->sprite_screen_x;
	if (calc->draw_end_x >= SCREEN_WIDTH)
		calc->draw_end_x = SCREEN_WIDTH - 1;
}
