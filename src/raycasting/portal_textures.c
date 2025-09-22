/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ju <ju@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ju                #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ju               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	select_prtl_texture(t_cub3d *cub3d, t_texture_calc *tex_calc,
		char map_char)
{
	int	i;
	int	current_animation_frame;

	if (!cub3d || !cub3d->tp_portals || cub3d->nb_portals <= 0)
		return ;
	tex_calc->is_portal = 1;
	i = 0;
	while (i < cub3d->nb_portals)
	{
		if (cub3d->tp_portals[i].name == map_char)
		{
			current_animation_frame = cub3d->prtl_sprites.current_frame
				% cub3d->prtl_sprites.frame_counter;
			tex_calc->portal_index = i;
			tex_calc->current_text
				= &cub3d->prtl_sprites.frames[current_animation_frame];
			return ;
		}
		i++;
	}
}

void	select_wall_normal_texture(t_cub3d *cub3d, t_dda *dda,
	t_texture_calc *tex_calc)
{
	if (dda->side == 0)
	{
		if (dda->ray_dir_x > 0)
			tex_calc->current_text = &cub3d->textures.west_img;
		else
			tex_calc->current_text = &cub3d->textures.east_img;
	}
	else
	{
		if (dda->ray_dir_y > 0)
			tex_calc->current_text = &cub3d->textures.north_img;
		else
			tex_calc->current_text = &cub3d->textures.south_img;
	}
}
