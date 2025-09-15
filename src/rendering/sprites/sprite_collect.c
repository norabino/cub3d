/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_collect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/15 19:56:49 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/* Calculate distance between player and sprite */
static double	calc_sprite_distance(t_cub3d *cub3d, double sprite_x,
	double sprite_y)
{
	double	dx;
	double	dy;

	dx = cub3d->player.pos_x - sprite_x;
	dy = cub3d->player.pos_y - sprite_y;
	return (dx * dx + dy * dy);
}

/* Check if sprite should be culled (too far or outside view) */
static int	should_cull_sprite(t_cub3d *cub3d, double sprite_x,
	double sprite_y)
{
	double	distance;
	double	dx;
	double	dy;
	double	dot_product;

	distance = calc_sprite_distance(cub3d, sprite_x, sprite_y);
	if (distance > MAX_SPRITE_DISTANCE * MAX_SPRITE_DISTANCE)
		return (1);
	dx = sprite_x - cub3d->player.pos_x;
	dy = sprite_y - cub3d->player.pos_y;
	dot_product = dx * cub3d->player.dir_x + dy * cub3d->player.dir_y;
	if (dot_product < -SPRITE_CULLING_THRESHOLD)
		return (1);
	return (0);
}

/* Add a single portal sprite to the sprite list */
static void	add_portal_sprite(t_cub3d *cub3d, int portal_idx)
{
	double		sprite_x;
	double		sprite_y;

	sprite_x = cub3d->tp_portals[portal_idx].p1.x + 0.5;
	sprite_y = cub3d->tp_portals[portal_idx].p1.y + 0.5;
	if (should_cull_sprite(cub3d, sprite_x, sprite_y))
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

/* Add the second portal point as a sprite */
static void	add_portal_sprite_p2(t_cub3d *cub3d, int portal_idx)
{
	double		sprite_x;
	double		sprite_y;

	sprite_x = cub3d->tp_portals[portal_idx].p2.x + 0.5;
	sprite_y = cub3d->tp_portals[portal_idx].p2.y + 0.5;
	if (should_cull_sprite(cub3d, sprite_x, sprite_y))
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

/* Collect all portal sprites for rendering */
void	collect_portal_sprites(t_cub3d *cub3d)
{
	int	i;

	printf("collect_portal_sprites: Starting\n");
	if (!cub3d)
		return ;
	
	// Allocate sprites array only once
	if (!cub3d->sprites)
	{
		cub3d->sprites = malloc(sizeof(t_sprite) * MAX_SPRITES);
		if (!cub3d->sprites)
			return ;
		printf("collect_portal_sprites: Allocated sprites array\n");
	}
	
	cub3d->sprite_count = 0;
	if (!cub3d->tp_portals || cub3d->nb_portals <= 0)
	{
		printf("collect_portal_sprites: No portals found\n");
		return ;
	}
	printf("collect_portal_sprites: Processing %d portals\n", cub3d->nb_portals);
	i = 0;
	while (i < cub3d->nb_portals)
	{
		printf("collect_portal_sprites: Processing portal %d\n", i);
		add_portal_sprite(cub3d, i);
		add_portal_sprite_p2(cub3d, i);
		i++;
	}
	printf("collect_portal_sprites: Done, count=%d\n", cub3d->sprite_count);
}
