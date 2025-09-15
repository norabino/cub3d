/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_collect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/15 21:44:31 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
#include <math.h>

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

/* Check if sprite is in field of view */
static int	is_sprite_in_fov(t_cub3d *cub3d, double sprite_x, double sprite_y)
{
	double	dx;
	double	dy;
	double	cross_product;
	double	dot_product;
	double	sprite_angle;
	
	dx = sprite_x - cub3d->player.pos_x;
	dy = sprite_y - cub3d->player.pos_y;
	
	// Calculer l'angle relatif du sprite par rapport à la direction du joueur
	dot_product = dx * cub3d->player.dir_x + dy * cub3d->player.dir_y;
	cross_product = dx * cub3d->player.dir_y - dy * cub3d->player.dir_x;
	sprite_angle = atan2(cross_product, dot_product);
	
	// Vérifier si le sprite est dans le FOV (environ 60 degrés = PI/3)
	return (fabs(sprite_angle) < M_PI / 3);
}

/* Check if sprite is occluded by walls using precise raycast */
static int	is_sprite_occluded(t_cub3d *cub3d, double sprite_x, double sprite_y)
{
	double	dx;
	double	dy;
	double	distance;
	double	step_x;
	double	step_y;
	double	current_x;
	double	current_y;
	int		steps;
	int		i;
	char	cell;
	int		hit_portal;
	
	dx = sprite_x - cub3d->player.pos_x;
	dy = sprite_y - cub3d->player.pos_y;
	distance = sqrt(dx * dx + dy * dy);
	
	// Si le sprite est très proche, il est toujours visible
	if (distance < 0.5)
		return (0);
	
	// Nombre de pas pour l'échantillonnage (plus de précision)
	steps = (int)(distance * 4);  // Plus précis
	if (steps < 20) steps = 20;
	if (steps > 200) steps = 200;
	
	step_x = dx / steps;
	step_y = dy / steps;
	
	current_x = cub3d->player.pos_x;
	current_y = cub3d->player.pos_y;
	hit_portal = 0;
	
	// Parcourir le chemin du joueur vers le sprite
	for (i = 1; i < steps - 1; i++)  // -1 pour ne pas tester la position du sprite lui-même
	{
		current_x += step_x;
		current_y += step_y;
		
		// Vérifier les limites de la carte
		if (current_x < 0 || current_y < 0)
			return (1);
		if ((int)current_y >= ft_tablen(cub3d->map))
			return (1);
		if ((int)current_x >= (int)strlen(cub3d->map[(int)current_y]))
			return (1);
			
		cell = cub3d->map[(int)current_y][(int)current_x];
		
		// Si on touche un mur et qu'on n'a pas encore traversé de portail
		if (cell == '1')
		{
			if (!hit_portal)
				return (1);  // Premier obstacle est un mur -> occulté
			else
				return (1);  // Mur après portail -> occulté aussi
		}
		
		// Si on traverse un portail, marquer qu'on en a vu un
		if (cell >= 'A' && cell <= 'Z')
			hit_portal = 1;
	}
	
	return (0);  // Chemin libre ou seulement des portails traversés
}

/* Check if sprite should be culled (too far, outside FOV, or occluded) */
static int	should_cull_sprite(t_cub3d *cub3d, double sprite_x,
	double sprite_y)
{
	double	distance;

	// Test de distance
	distance = calc_sprite_distance(cub3d, sprite_x, sprite_y);
	if (distance > MAX_SPRITE_DISTANCE * MAX_SPRITE_DISTANCE)
		return (1);
	
	// Test FOV
	if (!is_sprite_in_fov(cub3d, sprite_x, sprite_y))
		return (1);
		
	// Test d'occlusion
	if (is_sprite_occluded(cub3d, sprite_x, sprite_y))
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

	i = 0;
	if (!cub3d)
		return ;
	
	// Allocate sprites array only once
	if (!cub3d->sprites)
	{
		cub3d->sprites = malloc(sizeof(t_sprite) * MAX_SPRITES);
		if (!cub3d->sprites)
			return ;
	}
	
	cub3d->sprite_count = 0;
	if (!cub3d->tp_portals || cub3d->nb_portals <= 0)
		return ;
		
	while (i < cub3d->nb_portals)
	{
		add_portal_sprite(cub3d, i);
		add_portal_sprite_p2(cub3d, i);
		i++;
	}
}
