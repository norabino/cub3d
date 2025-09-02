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

static void	select_prtl_texture(t_cub3d *cub3d, t_texture_calc *tex_calc,
	char map_char)
{
	int	i;
	int	safe_frame;

	if (!cub3d || !tex_calc || !cub3d->tp_portals || cub3d->nb_portals <= 0)
		return ;
	tex_calc->is_portal = 1;
	i = 0;
	while (i < cub3d->nb_portals)
	{
		if (cub3d->tp_portals[i].name == map_char)
		{
			safe_frame = cub3d->tp_portals[i].sprite.current_frame % 4;
			tex_calc->portal_index = i;
			tex_calc->current_text
				= &cub3d->tp_portals[i].sprite.frames[safe_frame];
			tex_calc->portal_color[0]
				= cub3d->tp_portals[i].sprite.color_tint[0];
			tex_calc->portal_color[1]
				= cub3d->tp_portals[i].sprite.color_tint[1];
			tex_calc->portal_color[2]
				= cub3d->tp_portals[i].sprite.color_tint[2];
			return ;
		}
		i++;
	}
}

static void	select_wall_normal_texture(t_cub3d *cub3d, t_dda *dda,
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

void	select_wall_texture_extended(t_cub3d *cub3d, t_dda *dda,
	t_texture_calc *tex_calc)
{
	char	map_char;

	if (!tex_calc)
		return ;
	map_char = cub3d->map[(int)dda->map_y][(int)dda->map_x];
	tex_calc->is_portal = 0;
	if (is_lowercase(map_char))
		select_prtl_texture(cub3d, tex_calc, map_char);
	else
		select_wall_normal_texture(cub3d, dda, tex_calc);
}
