/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:30:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/26 20:50:03 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Version optimisée de draw_minimap_pixel avec pré-calculs
** Évite les calculs répétitifs et améliore les performances
*/
void	draw_minimap_pixel_optimized(t_cub3d *cub3d, t_pixel_draw *pixel)
{
	int	dx;
	int	dy;
	int	dist_sq;
	int	existing_color;
	int	blended_color;

	dx = pixel->x - pixel->center_x;
	dy = pixel->y - pixel->center_y;
	dist_sq = dx * dx + dy * dy;
	if (dist_sq <= (MINIMAP_SIZE / 2) * (MINIMAP_SIZE / 2))
	{
		if (dist_sq <= (MINIMAP_SIZE / 2 - 2) * (MINIMAP_SIZE / 2 - 2))
		{
			existing_color = get_pixel_color(cub3d->mlx.img, pixel->x,
					pixel->y);
			blended_color = alpha_blend(existing_color, 0x808080, 0.7);
			my_mlx_pixel_put(cub3d->mlx.img, pixel->x, pixel->y,
				blended_color);
		}
		else
			my_mlx_pixel_put(cub3d->mlx.img, pixel->x, pixel->y,
				MINIMAP_COLOR_BORDER);
	}
}

/*
** Calcule la largeur du triangle pour une ligne donnée
*/
int	get_triangle_half_width(int y)
{
	int	row_index;

	row_index = y + 9;
	if (row_index == 0 || row_index == 1)
		return (0);
	else if (row_index == 2 || row_index == 3)
		return (1);
	else if (row_index == 4 || row_index == 5)
		return (2);
	else if (row_index == 6 || row_index == 7)
		return (3);
	else
		return (4);
}

/*
** Dessine une ligne du triangle
*/
void	draw_triangle_line(t_cub3d *cub3d, t_triangle_draw *draw)
{
	int	x;

	x = -draw->half_width;
	while (x <= draw->half_width)
	{
		if (is_arrow_border(x, draw->y))
			my_mlx_pixel_put(cub3d->mlx.img, draw->center_x + x,
				draw->center_y + draw->y, MINIMAP_COLOR_WALL);
		else
			my_mlx_pixel_put(cub3d->mlx.img, draw->center_x + x,
				draw->center_y + draw->y, MINIMAP_COLOR_PLAYER);
		x++;
	}
}

/*
** Helper pour le blending des composantes de couleur
*/
int	blend_color_component(int bg_color, int fg_color, int alpha_int,
	int inv_alpha)
{
	int	bg_r;
	int	bg_g;
	int	bg_b;

	bg_r = (bg_color >> 16) & 0xFF;
	bg_g = (bg_color >> 8) & 0xFF;
	bg_b = bg_color & 0xFF;
	bg_r = (bg_r * inv_alpha + ((fg_color >> 16) & 0xFF) * alpha_int) >> 8;
	bg_g = (bg_g * inv_alpha + ((fg_color >> 8) & 0xFF) * alpha_int) >> 8;
	bg_b = (bg_b * inv_alpha + (fg_color & 0xFF) * alpha_int) >> 8;
	return ((bg_r << 16) | (bg_g << 8) | bg_b);
}
