/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/08/20 15:38:05 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Calculate texture coordinates for wall mapping - optimized */
void	calc_texture_coordinates(t_cub3d *cub3d, t_dda *dda,
	t_texture_calc *tex_calc, double perp_wall_dist)
{
	if (!cub3d || !dda || !tex_calc || !tex_calc->current_texture)
		return ;
	if (dda->side == 0)
		tex_calc->wall_x = cub3d->player.pos_y + perp_wall_dist
			* dda->ray_dir_y;
	else
		tex_calc->wall_x = cub3d->player.pos_x + perp_wall_dist
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
void	draw_textured_wall_pixels(t_cub3d *cub3d, int screen_x,
	t_texture_calc *tex_calc, int draw_params[2])
{
	int		y;
	int		tex_height;
	int		*draw_bounds[2];

	if (!cub3d || !tex_calc || !tex_calc->current_texture)
		return ;
	init_texture_draw_params(tex_calc, draw_params, &tex_height, draw_bounds);
	y = *draw_bounds[0];
	while (y < *draw_bounds[1])
	{
		draw_single_texture_pixel(cub3d, screen_x, y, tex_calc);
		y++;
	}
}
