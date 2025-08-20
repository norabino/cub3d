/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/08/20 15:37:33 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Calculate line height and draw boundaries */
void	calc_line_bounds(double perp_wall_dist, int *draw_start, int *draw_end)
{
	int	line_height;

	if (perp_wall_dist < 0.01)
		perp_wall_dist = 0.01;
	line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
	if (line_height > SCREEN_HEIGHT * 10)
		line_height = SCREEN_HEIGHT * 10;
	*draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (*draw_end >= SCREEN_HEIGHT)
		*draw_end = SCREEN_HEIGHT - 1;
}

/* Draw wall pixels helper function */
void	draw_wall_pixels(t_cub3d *cub3d, int screen_x, int draw_start,
	int draw_end)
{
	int	y;
	int	wall_color;

	wall_color = 0x00FF00;
	y = draw_start;
	while (y < draw_end)
	{
		my_mlx_pixel_put(cub3d->mlx.img, screen_x, y, wall_color);
		y++;
	}
}

/* Draw floor and ceiling helper function */
void	draw_floor_ceiling(t_cub3d *cub3d, int screen_x, int draw_start,
	int draw_end)
{
	int	y;
	int	floor_color;
	int	ceiling_color;

	floor_color = (cub3d->colors.floor[0] << 16)
		| (cub3d->colors.floor[1] << 8) | cub3d->colors.floor[2];
	ceiling_color = (cub3d->colors.ceiling[0] << 16)
		| (cub3d->colors.ceiling[1] << 8) | cub3d->colors.ceiling[2];
	y = 0;
	while (y < draw_start)
	{
		my_mlx_pixel_put(cub3d->mlx.img, screen_x, y, ceiling_color);
		y++;
	}
	y = draw_end;
	while (y < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(cub3d->mlx.img, screen_x, y, floor_color);
		y++;
	}
}

/* Draw vertical wall slice on screen with texture, floor and ceiling */
void	draw_wall_slice(t_cub3d *cub3d, int screen_x, double perp_wall_dist,
	t_dda *dda)
{
	int				draw_start;
	int				draw_end;
	int				draw_params[2];
	t_texture_calc	tex_calc;

	if (!cub3d || !dda)
		return ;
	calc_line_bounds(perp_wall_dist, &draw_start, &draw_end);
	select_wall_texture(cub3d, dda, &tex_calc);
	calc_texture_coordinates(cub3d, dda, &tex_calc, perp_wall_dist);
	tex_calc.perp_wall_dist = perp_wall_dist;
	draw_params[0] = draw_start;
	draw_params[1] = draw_end;
	draw_textured_wall_pixels(cub3d, screen_x, &tex_calc, draw_params);
	draw_floor_ceiling(cub3d, screen_x, draw_start, draw_end);
}
