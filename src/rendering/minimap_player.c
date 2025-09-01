/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ju <ju@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ju                #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ju               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Dessine le joueur comme une flèche de boussole rouge avec contour noir
** Optimisé: utilise la largeur pré-calculée pour chaque ligne
*/
void	draw_minimap_player(t_cub3d *cub3d, int center_x, int center_y)
{
	int				y;
	t_triangle_draw	draw;

	draw.center_x = center_x;
	draw.center_y = center_y;
	y = -9;
	while (y <= 0)
	{
		draw.y = y;
		draw.half_width = get_triangle_half_width(y);
		draw_triangle_line(cub3d, &draw);
		y++;
	}
}

/*
** Dessine un pixel de la minimap avec opacité selon sa distance du centre
** Utilise un vrai alpha blending avec les textures existantes
** Optimisé: calcul de distance optimisé avec early exit
*/
void	draw_minimap_pixel(t_cub3d *cub3d, int x, int y, int radius)
{
	int	dx;
	int	dy;
	int	dist_sq;
	int	existing_color;
	int	blended_color;

	dx = x - (MINIMAP_X + MINIMAP_SIZE / 2);
	dy = y - (MINIMAP_Y + MINIMAP_SIZE / 2);
	dist_sq = dx * dx + dy * dy;
	if (dist_sq <= radius * radius)
	{
		if (dist_sq <= (radius - 2) * (radius - 2))
		{
			existing_color = get_pixel_color(cub3d->mlx.img, x, y);
			blended_color = alpha_blend(existing_color, 0x808080, 0.7);
			my_mlx_pixel_put(cub3d->mlx.img, x, y, blended_color);
		}
		else
			my_mlx_pixel_put(cub3d->mlx.img, x, y, MINIMAP_COLOR_BORDER);
	}
}
