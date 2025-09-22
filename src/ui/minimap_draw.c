/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:30:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/22 18:03:41 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	copy_pattern_row(int *dst, int *src, int size)
{
	int	i;
	int	count;

	count = size / sizeof(int);
	i = 0;
	while (i < count)
	{
		dst[i] = src[i];
		i++;
	}
}

void	init_player_arrow_pattern(int pattern[8][9])
{
	copy_pattern_row(pattern[0], (int []){0, 0, 0, 0, 2, 0, 0, 0, 0}, 36);
	copy_pattern_row(pattern[1], (int []){0, 0, 0, 2, 1, 2, 0, 0, 0}, 36);
	copy_pattern_row(pattern[2], (int []){0, 0, 0, 2, 1, 2, 0, 0, 0}, 36);
	copy_pattern_row(pattern[3], (int []){0, 0, 2, 1, 1, 1, 2, 0, 0}, 36);
	copy_pattern_row(pattern[4], (int []){0, 0, 2, 1, 1, 1, 2, 0, 0}, 36);
	copy_pattern_row(pattern[5], (int []){0, 2, 1, 1, 1, 1, 1, 2, 0}, 36);
	copy_pattern_row(pattern[6], (int []){0, 2, 1, 1, 1, 1, 1, 2, 0}, 36);
	copy_pattern_row(pattern[7], (int []){2, 2, 2, 2, 2, 2, 2, 2, 2}, 36);
}

static int	get_arrow_pixel_color(t_cub3d *cub3d, int x, int y)
{
	if (cub3d->mini_map.arrow[y][x] == 1)
		return (MINIMAP_COLOR_PLAYER);
	else if (cub3d->mini_map.arrow[y][x] == 2)
		return (MINIMAP_COLOR_WALL);
	return (-1);
}

static void	draw_arrow_pixel(t_cub3d *cub3d, t_pixel_draw *pixel)
{
	int	final_color;
	int	pixel_x;
	int	pixel_y;

	final_color = get_arrow_pixel_color(cub3d, pixel->x, pixel->y);
	if (final_color != -1)
	{
		pixel_x = pixel->center_x - 4 + pixel->x;
		pixel_y = pixel->center_y - 5 + pixel->y;
		my_mlx_pixel_put(cub3d->mlx.img, pixel_x, pixel_y, final_color);
	}
}

void	draw_minimap_player(t_cub3d *cub3d, int center_x, int center_y)
{
	t_pixel_draw	pixel;
	int				y;
	int				x;

	if (!cub3d->mini_map.init)
	{
		init_player_arrow_pattern(cub3d->mini_map.arrow);
		cub3d->mini_map.init = 1;
	}
	pixel.center_x = center_x;
	pixel.center_y = center_y;
	y = 0;
	while (y < 8)
	{
		x = 0;
		while (x < 9)
		{
			pixel.x = x;
			pixel.y = y;
			draw_arrow_pixel(cub3d, &pixel);
			x++;
		}
		y++;
	}
}
