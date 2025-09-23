/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:00:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/23 15:00:39 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
			draw_minimap_pixel(cub3d, &pixel);
			x++;
		}
		y++;
	}
}

static int	is_wall_at_pos(t_cub3d *cub3d, double world_x, double world_y)
{
	if (world_x < 0 || world_y < 0)
		return (0);
	if ((int)world_y >= ft_tablen(cub3d->map))
		return (0);
	if (!cub3d->map[(int)world_y])
		return (0);
	if ((int)world_x >= (int)ft_strlen(cub3d->map[(int)world_y]))
		return (0);
	return (safe_map_access(cub3d, (int)world_y, (int)world_x) == '1');
}

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

void	draw_minimap(t_cub3d *cub3d)
{
	int	center_x;
	int	center_y;

	if (SCREEN_HEIGHT <= MINIMAP_SIZE
		|| SCREEN_WIDTH <= MINIMAP_SIZE)
		return ;
	center_x = MINIMAP_X + MINIMAP_SIZE / 2;
	center_y = MINIMAP_Y + MINIMAP_SIZE / 2;
	draw_minimap_background(cub3d, center_x, center_y);
	draw_minimap_walls(cub3d, center_x, center_y);
	draw_minimap_portals(cub3d, center_x, center_y);
	draw_minimap_player(cub3d, center_x, center_y);
}
