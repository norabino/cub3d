/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_alpha.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:00:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/22 18:02:40 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_pixel_color(t_img *img, int x, int y)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return (0x000000);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

int	alpha_blend(int bg_color, int fg_color, double alpha)
{
	int	alpha_int;
	int	inv_alpha;
	int	result;

	alpha_int = (int)(alpha * 256);
	inv_alpha = 256 - alpha_int;
	result = blend_color_component(bg_color, fg_color, alpha_int, inv_alpha);
	return (result);
}

int	blend_color_component(int bg_color, int fg_color, int alpha_int,
		int inv_alpha)
{
	int	bg_rgb[3];
	int	fg_rgb[3];
	int	result;

	bg_rgb[0] = (bg_color >> 16) & 0xFF;
	bg_rgb[1] = (bg_color >> 8) & 0xFF;
	bg_rgb[2] = bg_color & 0xFF;
	fg_rgb[0] = (fg_color >> 16) & 0xFF;
	fg_rgb[1] = (fg_color >> 8) & 0xFF;
	fg_rgb[2] = fg_color & 0xFF;
	bg_rgb[0] = (fg_rgb[0] * alpha_int + bg_rgb[0] * inv_alpha) >> 8;
	bg_rgb[1] = (fg_rgb[1] * alpha_int + bg_rgb[1] * inv_alpha) >> 8;
	bg_rgb[2] = (fg_rgb[2] * alpha_int + bg_rgb[2] * inv_alpha) >> 8;
	result = (bg_rgb[0] << 16) | (bg_rgb[1] << 8) | bg_rgb[2];
	return (result);
}

void	draw_minimap_pixel(t_cub3d *cub3d, t_pixel_draw *pixel)
{
	int		dx;
	int		dy;
	double	dist_sq;

	dx = pixel->x - pixel->center_x;
	dy = pixel->y - pixel->center_y;
	dist_sq = dx * dx + dy * dy;
	if (dist_sq <= (MINIMAP_SIZE / 2) * (MINIMAP_SIZE / 2))
	{
		if (dist_sq <= (MINIMAP_SIZE / 2 - 2) * (MINIMAP_SIZE / 2 - 2))
		{
			my_mlx_pixel_put(cub3d->mlx.img, pixel->x, pixel->y,
				MINIMAP_COLOR_BG);
		}
		else
		{
			my_mlx_pixel_put(cub3d->mlx.img, pixel->x, pixel->y,
				0x000000);
		}
	}
}
