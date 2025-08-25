/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:30:00 by norabino          #+#    #+#             */
/*   Updated: 2025/08/25 14:49:00 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Checks if a position is valid around the player with a safety margin
** Tests multiple points around the player position to create a collision
** "bubble" that prevents sticking to walls
** The COLLISION_MARGIN constant defines the minimum distance from walls
*/
int	is_valid_position(t_cub3d *cub3d, double x, double y)
{
	if (x < COLLISION_MARGIN || y < COLLISION_MARGIN)
		return (0);
	if (cub3d->map[(int)y] == NULL || cub3d->map[(int)y][(int)x] == '\0'
		|| cub3d->map[(int)y][(int)x] == '1')
		return (0);
	if (!check_corner_positions(cub3d, x, y))
		return (0);
	if (!check_bottom_corners(cub3d, x, y))
		return (0);
	return (1);
}

int	perpendicular_move(t_cub3d *cub3d, double new_x, double new_y)
{
	if (is_valid_position(cub3d, new_x, new_y))
	{
		cub3d->player.pos_x = new_x;
		cub3d->player.pos_y = new_y;
		return (1);
	}
	return (0);
}

int	horizontal_move(t_cub3d *cub3d, double new_x, double y)
{
	if (is_valid_position(cub3d, new_x, y))
	{
		cub3d->player.pos_x = new_x;
		cub3d->player.pos_y = y;
		return (1);
	}
	return (0);
}

int	vertical_move(t_cub3d *cub3d, double x, double new_y)
{
	if (is_valid_position(cub3d, x, new_y))
	{
		cub3d->player.pos_x = x;
		cub3d->player.pos_y = new_y;
		return (1);
	}
	return (0);
}

/*
** Déplace le joueur en vérifiant les collisions
** Teste la nouvelle position avant de s'y déplacer
** Si ça passe, on bouge. Si ça coince, on reste sur place
** Retourne 1 si le mouvement a eu lieu, 0 sinon
*/
int	move_player(t_cub3d *cub3d, double delta_x, double delta_y)
{
	double	new_x;
	double	new_y;

	new_x = cub3d->player.pos_x + delta_x;
	new_y = cub3d->player.pos_y + delta_y;
	if (!perpendicular_move(cub3d, new_x, new_y)
		&& !horizontal_move(cub3d, new_x, cub3d->player.pos_y)
		&& !vertical_move(cub3d, cub3d->player.pos_x, new_y))
		return (0);
	return (1);
}
