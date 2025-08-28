/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:00:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/29 00:32:20 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Vérifie si un point est dans le cercle de la minimap
** Optimisé: évite sqrt() pour de meilleures performances
*/
int	is_point_in_circle(int x, int y, int radius)
{
	int	dx;
	int	dy;

	dx = x;
	dy = y;
	return (dx * dx + dy * dy <= radius * radius);
}

/*
** Dessine le fond rond gris de la minimap avec le contour noir
** Optimisé: pré-calcule les valeurs constantes et utilise early exit
*/
void	draw_minimap_background(t_cub3d *cub3d, int center_x, int center_y)
{
	int				x;
	int				y;
	int				radius;
	t_pixel_draw	pixel;

	radius = MINIMAP_SIZE / 2;
	pixel.center_x = center_x;
	pixel.center_y = center_y;
	y = center_y - radius;
	while (y <= center_y + radius)
	{
		x = center_x - radius;
		while (x <= center_x + radius)
		{
			pixel.x = x;
			pixel.y = y;
			draw_minimap_pixel_optimized(cub3d, &pixel);
			x++;
		}
		y++;
	}
}

/*
** Dessine les murs de la carte sur la minimap
** Optimisé pour les FPS et conforme à la norme
*/
void	draw_minimap_walls(t_cub3d *cub3d, int center_x, int center_y)
{
	t_minimap_calc		calc;
	t_minimap_screen	screen;
	t_minimap_render	render;

	init_minimap_calc(cub3d, &calc);
	render.screen_y = -MINIMAP_SIZE / 2;
	while (render.screen_y < MINIMAP_SIZE / 2)
	{
		render.screen_x = -MINIMAP_SIZE / 2;
		while (render.screen_x < MINIMAP_SIZE / 2)
		{
			screen.x = render.screen_x;
			screen.y = render.screen_y;
			calculate_world_pos(&render.world_x, &render.world_y,
				&calc, &screen);
			if (is_wall_at_pos(cub3d, render.world_x, render.world_y)
				&& is_point_in_circle(render.screen_x, render.screen_y,
					MINIMAP_SIZE / 2 - 2))
				my_mlx_pixel_put(cub3d->mlx.img, center_x + render.screen_x,
					center_y + render.screen_y, MINIMAP_COLOR_WALL);
			render.screen_x++;
		}
		render.screen_y++;
	}
}

/*
** Dessine les portails sur la minimap en couleur bleu/violet galaxie
** Optimisé pour les FPS et conforme à la norme
*/
void	draw_minimap_portals(t_cub3d *cub3d, int center_x, int center_y)
{
	t_minimap_calc		calc;
	t_minimap_screen	screen;
	t_minimap_render	render;

	init_minimap_calc(cub3d, &calc);
	render.screen_y = -MINIMAP_SIZE / 2;
	while (render.screen_y < MINIMAP_SIZE / 2)
	{
		render.screen_x = -MINIMAP_SIZE / 2;
		while (render.screen_x < MINIMAP_SIZE / 2)
		{
			screen.x = render.screen_x;
			screen.y = render.screen_y;
			calculate_world_pos(&render.world_x, &render.world_y,
				&calc, &screen);
			if (is_portal_at_pos(cub3d, render.world_x, render.world_y)
				&& is_point_in_circle(render.screen_x, render.screen_y,
					MINIMAP_SIZE / 2 - 2))
				my_mlx_pixel_put(cub3d->mlx.img, center_x + render.screen_x,
					center_y + render.screen_y, MINIMAP_COLOR_PORTAL);
			render.screen_x++;
		}
		render.screen_y++;
	}
}

/*
** Fonction principale qui dessine toute la minimap
** Comme peindre un tableau : d'abord le fond, puis les détails
** et enfin le personnage principal au premier plan
*/
void	draw_minimap(t_cub3d *cub3d)
{
	int	center_x;
	int	center_y;

	center_x = MINIMAP_X + MINIMAP_SIZE / 2;
	center_y = MINIMAP_Y + MINIMAP_SIZE / 2;
	draw_minimap_background(cub3d, center_x, center_y);
	draw_minimap_walls(cub3d, center_x, center_y);
	draw_minimap_portals(cub3d, center_x, center_y);
	draw_minimap_player(cub3d, center_x, center_y);
}
