/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_collect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:00:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/16 10:38:20 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
#include <math.h>
#include <stdlib.h>

static int	check_sprite_visibility(t_cub3d *cub3d, double x, double y)
{
	double	dx;
	double	dy;
	double	dist_sq;

	dx = x - cub3d->player.pos_x;
	dy = y - cub3d->player.pos_y;
	dist_sq = dx * dx + dy * dy;
	if (dist_sq > MAX_SPRITE_DISTANCE * MAX_SPRITE_DISTANCE)
		return (0);
	if (check_map_bounds(cub3d, x, y))
		return (0);
	if (!is_sprite_in_fov(cub3d, x, y))
		return (0);
	return (1);
}

static void	get_portal_position(t_cub3d *cub3d, int idx, int type, double *pos)
{
	if (type == 1)
	{
		pos[0] = cub3d->tp_portals[idx].p1.x + 0.5;
		pos[1] = cub3d->tp_portals[idx].p1.y + 0.5;
	}
	else
	{
		pos[0] = cub3d->tp_portals[idx].p2.x + 0.5;
		pos[1] = cub3d->tp_portals[idx].p2.y + 0.5;
	}
}

static void	add_single_portal_sprite(t_cub3d *cub3d, int idx, int type)
{
	t_sprite	*sprite;
	double		pos[2];
	double		dx;
	double		dy;

	if (!cub3d->tp_portals || idx < 0)
		return ;
	get_portal_position(cub3d, idx, type, pos);
	if (!check_sprite_visibility(cub3d, pos[0], pos[1]))
		return ;
	sprite = &cub3d->sprites[cub3d->sprite_count++];
	sprite->x = pos[0];
	sprite->y = pos[1];
	dx = cub3d->player.pos_x - pos[0];
	dy = cub3d->player.pos_y - pos[1];
	sprite->distance = dx * dx + dy * dy;
	sprite->portal_index = idx;
	sprite->portal_name = cub3d->tp_portals[idx].name;
}

static void	process_portal_pair(t_cub3d *cub3d, int idx)
{
	if (idx >= cub3d->nb_portals)
		return ;
	if (cub3d->sprite_count >= MAX_SPRITES - 1)
		return ;
	add_single_portal_sprite(cub3d, idx, 1);
	if (cub3d->sprite_count < MAX_SPRITES)
		add_single_portal_sprite(cub3d, idx, 2);
}

void	collect_portal_sprites(t_cub3d *cub3d)
{
	int	i;

	if (!cub3d)
		return ;
	if (!cub3d->sprites)
	{
		cub3d->sprites = malloc(sizeof(t_sprite) * MAX_SPRITES);
		if (!cub3d->sprites)
			return ;
	}
	cub3d->sprite_count = 0;
	if (!cub3d->tp_portals || cub3d->nb_portals <= 0)
		return ;
	i = 0;
	while (i < cub3d->nb_portals)
	{
		process_portal_pair(cub3d, i);
		i++;
	}
}
