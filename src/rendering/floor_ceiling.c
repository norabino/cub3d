/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:32:24 by norabino          #+#    #+#             */
/*   Updated: 2025/09/22 16:36:45 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	render_fc_textures(t_cub3d *cub3d, int screen_x,
	int draw_start, int draw_end)
{
	if (!cub3d->textures.ceiling_img.img && !cub3d->textures.floor_img.img)
		return ;
	if (cub3d->textures.ceiling_img.img)
		render_ceiling_texture(cub3d, screen_x, draw_start);
	if (cub3d->textures.floor_img.img)
		render_floor_texture(cub3d, screen_x, draw_end);
}

void	render_ceiling_texture(t_cub3d *cub3d, int screen_x, int draw_start)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		render_fc_pixel(cub3d, screen_x, y, &cub3d->textures.ceiling_img);
		y++;
	}
}

void	render_floor_texture(t_cub3d *cub3d, int screen_x, int draw_end)
{
	int	y;

	y = draw_end;
	while (y < SCREEN_HEIGHT)
	{
		render_fc_pixel(cub3d, screen_x, y, &cub3d->textures.floor_img);
		y++;
	}
}

void	render_fc_colors(t_cub3d *cub3d, int screen_x,
	int draw_start, int draw_end)
{
	render_ceiling_color(cub3d, screen_x, draw_start);
	render_floor_color(cub3d, screen_x, draw_end);
}
