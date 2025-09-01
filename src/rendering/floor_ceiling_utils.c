/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:50:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/01 20:40:54 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	render_fc_pixel(t_cub3d *cub3d, int screen_x, int y,
	t_texture_img *texture)
{
	double		row_distance;
	double		floor_step_x;
	double		floor_step_y;
	t_fc_coords	coords;

	if (!texture || !texture->img)
		return ;
	if (y == SCREEN_HEIGHT / 2)
		return ;
	if (y < SCREEN_HEIGHT / 2)
		row_distance = SCREEN_HEIGHT / (SCREEN_HEIGHT - 2.0 * y);
	else
		row_distance = SCREEN_HEIGHT / (2.0 * y - SCREEN_HEIGHT);
	floor_step_x = row_distance * (cub3d->player.dir_x + cub3d->view.plane_x
			- (cub3d->player.dir_x - cub3d->view.plane_x)) / SCREEN_WIDTH;
	floor_step_y = row_distance * (cub3d->player.dir_y + cub3d->view.plane_y
			- (cub3d->player.dir_y - cub3d->view.plane_y)) / SCREEN_WIDTH;
	coords.floor_x = cub3d->player.pos_x + row_distance * (cub3d->player.dir_x
			- cub3d->view.plane_x) + floor_step_x * screen_x;
	coords.floor_y = cub3d->player.pos_y + row_distance * (cub3d->player.dir_y
			- cub3d->view.plane_y) + floor_step_y * screen_x;
	coords.screen_x = screen_x;
	coords.y = y;
	apply_fc_texture(cub3d, texture, &coords);
}

void	apply_fc_texture(t_cub3d *cub3d, t_texture_img *texture,
	t_fc_coords *coords)
{
	int	tex_x;
	int	tex_y;
	int	color;

	if (!texture || !texture->img || texture->width <= 0
		|| texture->height <= 0)
		return ;
	tex_x = (int)(texture->width * (coords->floor_x - (int)coords->floor_x));
	tex_y = (int)(texture->height * (coords->floor_y - (int)coords->floor_y));
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	color = get_texture_pixel_color(texture, tex_x, tex_y);
	my_mlx_pixel_put(cub3d->mlx.img, coords->screen_x, coords->y, color);
}

void	render_ceiling_color(t_cub3d *cub3d, int screen_x, int draw_start)
{
	int	ceiling_color;
	int	y;

	if (cub3d->textures.ceiling_img.img)
		return ;
	ceiling_color = (cub3d->colors.ceiling[0] << 16)
		| (cub3d->colors.ceiling[1] << 8) | cub3d->colors.ceiling[2];
	y = 0;
	while (y < draw_start)
	{
		my_mlx_pixel_put(cub3d->mlx.img, screen_x, y, ceiling_color);
		y++;
	}
}

void	render_floor_color(t_cub3d *cub3d, int screen_x, int draw_end)
{
	int	floor_color;
	int	y;

	if (cub3d->textures.floor_img.img)
		return ;
	floor_color = (cub3d->colors.floor[0] << 16)
		| (cub3d->colors.floor[1] << 8) | cub3d->colors.floor[2];
	y = draw_end;
	while (y < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(cub3d->mlx.img, screen_x, y, floor_color);
		y++;
	}
}
