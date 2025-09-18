/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_collect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/18 20:54:52 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

double	calc_sprite_distance(t_cub3d *cub3d, double sprite_x, double sprite_y)
{
	double	dx;
	double	dy;

	dx = cub3d->player.pos_x - sprite_x;
	dy = cub3d->player.pos_y - sprite_y;
	return (dx * dx + dy * dy);
}

int	is_sprite_in_fov(t_cub3d *cub3d, double sprite_x, double sprite_y)
{
	double	dx;
	double	dy;
	double	dot_product;
	double	cross_product;

	dx = sprite_x - cub3d->player.pos_x;
	dy = sprite_y - cub3d->player.pos_y;
	dot_product = dx * cub3d->player.dir_x + dy * cub3d->player.dir_y;
	cross_product = dx * cub3d->player.dir_y - dy * cub3d->player.dir_x;
	return (fabs(atan2(cross_product, dot_product)) < M_PI / 2);
}

static void	add_portal_sprite(t_cub3d *cub3d, int portal_idx, int flg)
{
	double	sprite_x;
	double	sprite_y;

	if (flg == 1)
	{
		sprite_x = cub3d->tp_portals[portal_idx].p1.x + 0.5;
		sprite_y = cub3d->tp_portals[portal_idx].p1.y + 0.5;
	}
	else
	{
		sprite_x = cub3d->tp_portals[portal_idx].p2.x + 0.5;
		sprite_y = cub3d->tp_portals[portal_idx].p2.y + 0.5;
	}
	if (should_display_sprite(cub3d, sprite_x, sprite_y))
		return ;
	if (cub3d->sprite_count >= MAX_SPRITES)
		return ;
	cub3d->sprites[cub3d->sprite_count].x = sprite_x;
	cub3d->sprites[cub3d->sprite_count].y = sprite_y;
	cub3d->sprites[cub3d->sprite_count].distance = calc_sprite_distance(cub3d,
			sprite_x, sprite_y);
	cub3d->sprites[cub3d->sprite_count].portal_index = portal_idx;
	cub3d->sprites[cub3d->sprite_count].portal_name
		= cub3d->tp_portals[portal_idx].name;
	cub3d->sprite_count++;
}

void	collect_portal_sprites(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	if (!cub3d->sprites)
	{
		cub3d->sprites = malloc(sizeof(t_sprite) * MAX_SPRITES);
		if (!cub3d->sprites)
			exit_error("Failed to allocate sprite memory", cub3d);
	}
	cub3d->sprite_count = 0;
	if (!cub3d->tp_portals || cub3d->nb_portals <= 0)
		return ;
	while (i < cub3d->nb_portals)
	{
		add_portal_sprite(cub3d, i, 1);
		add_portal_sprite(cub3d, i, 2);
		i++;
	}
}
