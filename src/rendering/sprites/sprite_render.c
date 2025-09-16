/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/16 16:17:14 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/* Check if color should be treated as transparent */
int	is_transparent_color(int color)
{
	if (color < 0x014B63)
		return (1);
	return (0);
}

/* Update z-buffer for depth testing */
void	update_zbuffer(t_cub3d *cub3d, int x, double distance)
{
	if (x >= 0 && x < SCREEN_WIDTH && distance < cub3d->zbuffer.buffer[x])
		cub3d->zbuffer.buffer[x] = distance;
}

/* Draw a pixel with transparency check */
void	draw_transparent_pixel(t_cub3d *cub3d, int x, int y, int color)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	if (!is_transparent_color(color))
		my_mlx_pixel_put(cub3d->mlx.img, x, y, color);
}

/* Draw sprite pixels with transparency and depth testing */
void	draw_sprite_pixels(t_cub3d *cub3d, t_sprite *sprite,
	t_sprite_calc *calc)
{
	t_sprite_render_data	render_data;

	(void)sprite;
	if (calc->transform_y <= 0)
		return ;
	if (!cub3d->prtl_sprites.frames || cub3d->prtl_sprites.frame_counter <= 0)
		return ;
	render_data.current_frame = cub3d->prtl_sprites.current_frame
		% cub3d->prtl_sprites.frame_counter;
	render_data.current_texture = &cub3d->prtl_sprites.frames[
		render_data.current_frame];
	if (!render_data.current_texture || !render_data.current_texture->img
		|| render_data.current_texture->width <= 0
		|| render_data.current_texture->height <= 0)
		return ;
	render_data.x = calc->draw_start_x;
	while (render_data.x < calc->draw_end_x)
	{
		render_sprite_column(cub3d, calc, &render_data);
		render_data.x++;
	}
}
