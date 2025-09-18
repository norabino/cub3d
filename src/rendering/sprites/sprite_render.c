/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/18 20:14:47 by norabino         ###   ########.fr       */
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

/* Check if sprite is valid and visible */
static int	is_sprite_valid(t_cub3d *cub3d, t_sprite_calc *calc)
{
	if (calc->transform_y <= 0)
		return (0);
	if (!cub3d->prtl_sprites.frames || cub3d->prtl_sprites.frame_counter <= 0)
		return (0);
	return (1);
}

/* Initialize sprite render data */
static void	init_sprite_render_data(t_cub3d *cub3d,
	t_sprite_render_data *render_data)
{
	render_data->current_frame = cub3d->prtl_sprites.current_frame
		% cub3d->prtl_sprites.frame_counter;
	render_data->current_texture = &cub3d->prtl_sprites.frames[
		render_data->current_frame];
}

/* Validate sprite texture */
static int	is_texture_valid(t_sprite_render_data *render_data)
{
	if (!render_data->current_texture
		|| !render_data->current_texture->img
		|| render_data->current_texture->width <= 0
		|| render_data->current_texture->height <= 0)
		return (0);
	return (1);
}

/* Draw sprite pixels with transparency and depth testing */
void	draw_sprite_pixels(t_cub3d *cub3d, t_sprite *sprite,
	t_sprite_calc *calc)
{
	t_sprite_render_data	render_data;
	double					sprite_distance;

	if (!is_sprite_valid(cub3d, calc))
		return ;
	sprite_distance = sqrt((sprite->x - cub3d->player.pos_x)
			* (sprite->x - cub3d->player.pos_x)
			+ (sprite->y - cub3d->player.pos_y)
			* (sprite->y - cub3d->player.pos_y));
	init_sprite_render_data(cub3d, &render_data);
	if (!is_texture_valid(&render_data))
		return ;
	render_data.x = calc->draw_start_x;
	while (render_data.x < calc->draw_end_x)
	{
		render_sprite_column(cub3d, calc, &render_data, sprite_distance);
		render_data.x++;
	}
}
