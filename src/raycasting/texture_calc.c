/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/08/20 15:06:16 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define SCREEN_HEIGHT 720

/* Calculate texture coordinates for wall mapping - optimized */
void	calc_texture_coordinates(t_cub3d *cub3d, t_dda *dda,
	t_texture_calc *tex_calc, double perp_wall_dist)
{
	if (!cub3d || !dda || !tex_calc || !tex_calc->current_texture)
		return ;
	if (dda->side == 0)
		tex_calc->wall_x = cub3d->player.posY + perp_wall_dist
			* dda->ray_dir_y;
	else
		tex_calc->wall_x = cub3d->player.posX + perp_wall_dist
			* dda->ray_dir_x;
	tex_calc->wall_x -= (int)tex_calc->wall_x;
	tex_calc->tex_x = (int)(tex_calc->wall_x
			* tex_calc->current_texture->width);
	if ((dda->side == 0 && dda->ray_dir_x > 0)
		|| (dda->side == 1 && dda->ray_dir_y < 0))
		tex_calc->tex_x = tex_calc->current_texture->width
			- tex_calc->tex_x - 1;
}

/* Get pixel color from texture - fast version with bitwise operations */
int	get_texture_pixel_color(t_texture_img *texture, int x, int y)
{
	int	offset;

	if (!texture || !texture->addr)
		return (0x000000);
	x &= (texture->width - 1);
	y &= (texture->height - 1);
	offset = y * texture->line_length + x * (texture->bits_per_pixel >> 3);
	return (*(int *)(texture->addr + offset));
}

/* Draw textured wall pixels with correct proportions for close walls */
void	draw_textured_wall_pixels(t_cub3d *cub3d, int screen_x, int draw_start,
	int draw_end, t_texture_calc *tex_calc, double perp_wall_dist)
{
	int		y;
	int		real_wall_height;
	int		color;
	int		tex_height;

	if (!cub3d || !tex_calc || !tex_calc->current_texture)
		return ;
	real_wall_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
	tex_height = tex_calc->current_texture->height;
	tex_calc->step = (double)tex_height / real_wall_height;
	tex_calc->tex_pos = (draw_start - SCREEN_HEIGHT / 2
			+ real_wall_height / 2) * tex_calc->step;
	y = draw_start;
	while (y < draw_end)
	{
		tex_calc->tex_y = (int)tex_calc->tex_pos;
		if (tex_calc->tex_y >= tex_height)
			tex_calc->tex_y = tex_height - 1;
		else if (tex_calc->tex_y < 0)
			tex_calc->tex_y = 0;
		tex_calc->tex_pos += tex_calc->step;
		color = get_texture_pixel_color(tex_calc->current_texture,
				tex_calc->tex_x, tex_calc->tex_y);
		my_mlx_pixel_put(cub3d->mlx.img, screen_x, y, color);
		y++;
	}
}
