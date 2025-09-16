/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:00:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/16 02:09:38 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	is_transparent_color(int color)
{
	if (color < 0x014B63)
		return (1);
	return (0);
}

void	update_zbuffer(t_cub3d *cub3d, int x, double distance)
{
	if (x >= 0 && x < SCREEN_WIDTH && distance < cub3d->zbuffer.buffer[x])
		cub3d->zbuffer.buffer[x] = distance;
}

void	draw_transparent_pixel(t_cub3d *cub3d, int x, int y, int color)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	if (!is_transparent_color(color))
		my_mlx_pixel_put(cub3d->mlx.img, x, y, color);
}

void	draw_sprite_pixels(t_cub3d *cub3d, t_sprite *sprite,
	t_sprite_calc *calc)
{
	int	x;

	(void)sprite;
	if (calc->transform_y <= 0)
		return ;
	x = calc->draw_start_x;
	while (x < calc->draw_end_x)
	{
		if (x >= 0 && x < SCREEN_WIDTH
			&& calc->transform_y < cub3d->zbuffer.buffer[x])
		{
			draw_sprite_column(cub3d, calc, x);
		}
		x++;
	}
}
