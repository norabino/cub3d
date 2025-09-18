/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:46:46 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/18 19:30:52 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	render_sprite_column_pixels(t_cub3d *cub3d, t_sprite_calc *calc,
	t_sprite_render_data *render_data, double sprite_distance)
{
	int		tex_y;
	int		color;
	int		y;

	y = calc->draw_start_y;
	
	while (y < calc->draw_end_y)
	{
		// Vérifier le z-buffer pour l'occultation partielle avec tolérance
		if (cub3d->depth_buffer.buffer && render_data->x >= 0 
			&& render_data->x < SCREEN_WIDTH)
		{
			// Ajouter une tolérance plus importante pour éviter de cacher les sprites trop facilement
			if (sprite_distance > cub3d->depth_buffer.buffer[render_data->x] + 0.2)
			{
				y++;
				continue; // Ce pixel est derrière un mur, on passe au suivant
			}
		}
		
		tex_y = (y - calc->draw_start_y) * render_data->current_texture->height
			/ calc->sprite_height;
		if (render_data->tex_x >= 0
			&& render_data->tex_x < render_data->current_texture->width
			&& tex_y >= 0 && tex_y < render_data->current_texture->height)
		{
			color = get_texture_pixel_color(render_data->current_texture,
					render_data->tex_x, tex_y);
			if (!is_transparent_color(color))
				my_mlx_pixel_put(cub3d->mlx.img, render_data->x, y, color);
		}
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
	{
		render_sprite_column_pixels(cub3d, calc, render_data, sprite_distance);
	}
}
