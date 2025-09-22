/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:46:46 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/22 16:28:27 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	draw_transparent_pixel(t_cub3d *cub3d, int x, int y, int color)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	if (!is_transparent_color(color))
		my_mlx_pixel_put(cub3d->mlx.img, x, y, color);
}

/* Check depth buffer for occlusion */
static int	is_pixel_hidden(t_cub3d *cub3d, int x, double sprite_distance)
{
	if (!cub3d->depth_buffer.buffer || x < 0 || x >= SCREEN_WIDTH)
		return (0);
	if (sprite_distance > cub3d->depth_buffer.buffer[x] + 0.2)
		return (1);
	return (0);
}

static void	render_sprite_pixel(t_cub3d *cub3d, t_sprite_render_data *data,
	int tex_y, int y)
{
	int	color;

	if (data->tex_x >= 0 && data->tex_x < data->current_texture->width
		&& tex_y >= 0 && tex_y < data->current_texture->height)
	{
		color = get_texture_pixel_color(data->current_texture,
				data->tex_x, tex_y);
		if (!is_transparent_color(color))
			my_mlx_pixel_put(cub3d->mlx.img, data->x, y, color);
	}
}

static void	render_sprite_column_pixels(t_cub3d *cub3d, t_sprite_calc *calc,
	t_sprite_render_data *render_data, double sprite_distance)
{
	int	tex_y;
	int	y;

	y = calc->draw_start_y;
	while (y < calc->draw_end_y)
	{
		if (is_pixel_hidden(cub3d, render_data->x, sprite_distance))
		{
			y++;
			continue ;
		}
		tex_y = (y - calc->draw_start_y) * render_data->current_texture->height
			/ calc->sprite_height;
		render_sprite_pixel(cub3d, render_data, tex_y, y);
		y++;
	}
}

void	render_sprite_column(t_cub3d *cub3d, t_sprite_calc *calc,
	t_sprite_render_data *render_data, double sprite_distance)
{
	double	sprite_tex_x;

	sprite_tex_x = (double)(render_data->x - calc->sprite_screen_x
			+ calc->sprite_width / 2) / calc->sprite_width;
	render_data->tex_x = (int)(sprite_tex_x
			* render_data->current_texture->width);
	if (render_data->tex_x < 0)
		render_data->tex_x = 0;
	if (render_data->tex_x >= render_data->current_texture->width)
		render_data->tex_x = render_data->current_texture->width - 1;
	if (render_data->x >= 0 && render_data->x < SCREEN_WIDTH
		&& calc->transform_y > 0.1)
		render_sprite_column_pixels(cub3d, calc, render_data, sprite_distance);
}
