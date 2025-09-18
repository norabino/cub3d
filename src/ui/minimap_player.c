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

/* Dessine le joueur comme une flèche de boussole rouge avec contour noir */
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
