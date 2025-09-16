/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:00:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/16 02:25:31 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	draw_sprite_column(t_cub3d *cub3d, t_sprite_calc *calc, int x)
{
	int			y;
	int			tex_x;
	int			tex_y;
	int			color;
	t_txt_i		*texture;

	if (x < calc->draw_start_x || x >= calc->draw_end_x)
		return ;
	texture = get_current_portal_texture(cub3d);
	if (!texture || !texture->addr)
		return ;
	tex_x = (int)((x - calc->draw_start_x) * texture->width
			/ calc->sprite_width);
	y = calc->draw_start_y;
	while (y < calc->draw_end_y)
	{
		tex_y = (int)((y - calc->draw_start_y) * texture->height
				/ calc->sprite_height);
		color = get_texture_pixel(texture, tex_x, tex_y);
		if (!is_transparent_color(color))
			my_mlx_pixel_put(cub3d->mlx.img, x, y, color);
		y++;
	}
}

t_txt_i	*get_current_portal_texture(t_cub3d *cub3d)
{
	int	current_frame;

	if (!cub3d->prtl_sprites.frames || cub3d->prtl_sprites.frame_counter <= 0)
		return (NULL);
	current_frame = cub3d->prtl_sprites.current_frame
		% cub3d->prtl_sprites.frame_counter;
	return (&cub3d->prtl_sprites.frames[current_frame]);
}

int	get_texture_pixel(t_txt_i *texture, int x, int y)
{
	int	*data;
	int	index;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	data = (int *)texture->addr;
	index = y * texture->width + x;
	return (data[index]);
}
