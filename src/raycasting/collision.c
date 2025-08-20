/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:30:00 by norabino          #+#    #+#             */
/*   Updated: 2025/08/20 15:28:20 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Check if a position is valid (not a wall) with margin */
int	is_valid_position(t_cub3d *cub3d, double x, double y)
{
	if (!cub3d || !cub3d->map)
		return (0);
	if (x < 0.05 || y < 0.05)
		return (0);
	if (cub3d->map[(int)y] == NULL)
		return (0);
	if (cub3d->map[(int)y][(int)x] == '\0')
		return (0);
	if (cub3d->map[(int)y][(int)x] == '1')
		return (0);
	return (1);
}

/* Move player with collision detection */
int	move_player(t_cub3d *cub3d, double delta_x, double delta_y)
{
	double	new_x;
	double	new_y;

	if (!cub3d)
		return (0);
	new_x = cub3d->player.pos_x + delta_x;
	new_y = cub3d->player.pos_y + delta_y;
	if (is_valid_position(cub3d, new_x, cub3d->player.pos_y)
		&& is_valid_position(cub3d, cub3d->player.pos_x, new_y))
	{
		cub3d->player.pos_x = new_x;
		cub3d->player.pos_y = new_y;
		return (1);
	}
	return (0);
}
