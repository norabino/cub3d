/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/15 21:40:53 by norabino         ###   ########.fr       */
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
	int				x;
	int				y;
	int				tex_x;
	int				tex_y;
	int				color;
	int				current_frame;
	t_texture_img	*current_texture;
	double			sprite_tex_x;

	(void)sprite;
	if (calc->transform_y <= 0)
		return ;
	
	// Vérifier que les textures de portail sont initialisées
	if (!cub3d->prtl_sprites.frames || cub3d->prtl_sprites.frame_counter <= 0)
		return ;
	
	current_frame = cub3d->prtl_sprites.current_frame
		% cub3d->prtl_sprites.frame_counter;
	current_texture = &cub3d->prtl_sprites.frames[current_frame];
	
	// Vérifier que la texture courante est valide
	if (!current_texture || !current_texture->img || current_texture->width <= 0 || current_texture->height <= 0)
		return ;
		
	x = calc->draw_start_x;
	while (x < calc->draw_end_x)
	{
		// CORRECTION : calcul correct de la position dans la texture
		// comme pour les murs, basé sur la position relative du pixel
		sprite_tex_x = (double)(x - calc->sprite_screen_x + calc->sprite_width / 2) / calc->sprite_width;
		tex_x = (int)(sprite_tex_x * current_texture->width);
		
		// S'assurer que tex_x est dans les limites
		if (tex_x < 0) tex_x = 0;
		if (tex_x >= current_texture->width) tex_x = current_texture->width - 1;
		
		if (x >= 0 && x < SCREEN_WIDTH && calc->transform_y > 0.1)
		{
			y = calc->draw_start_y;
			while (y < calc->draw_end_y)
			{
				tex_y = (y - calc->draw_start_y) * current_texture->height
					/ calc->sprite_height;
				if (tex_x >= 0 && tex_x < current_texture->width
					&& tex_y >= 0 && tex_y < current_texture->height)
				{
					color = get_texture_pixel_color(current_texture, tex_x, tex_y);
					if (!is_transparent_color(color))
						my_mlx_pixel_put(cub3d->mlx.img, x, y, color);
				}
				y++;
			}
		}
		x++;
	}
}
