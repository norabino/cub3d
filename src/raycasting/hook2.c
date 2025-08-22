/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:30:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/22 17:04:51 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_movement(t_cub3d *cub3d)
{
	double	delta_x;
	double	delta_y;
	int		moved;

	moved = 0;
	if (cub3d->keys[KEY_W])
	{
		delta_x = cub3d->player.dir_x * MOVE_SPEED;
		delta_y = cub3d->player.dir_y * MOVE_SPEED;
		moved += move_player(cub3d, delta_x, delta_y);
	}
	if (cub3d->keys[KEY_S])
	{
		delta_x = -cub3d->player.dir_x * MOVE_SPEED;
		delta_y = -cub3d->player.dir_y * MOVE_SPEED;
		moved += move_player(cub3d, delta_x, delta_y);
	}
	return (moved + handle_movement_strafe(cub3d));
}

int	handle_movement_strafe(t_cub3d *cub3d)
{
	double	delta_x;
	double	delta_y;
	int		moved;

	moved = 0;
	if (cub3d->keys[KEY_A])
	{
		delta_x = cub3d->player.dir_y * MOVE_SPEED;
		delta_y = -cub3d->player.dir_x * MOVE_SPEED;
		moved += move_player(cub3d, delta_x, delta_y);
	}
	if (cub3d->keys[KEY_D])
	{
		delta_x = -cub3d->player.dir_y * MOVE_SPEED;
		delta_y = cub3d->player.dir_x * MOVE_SPEED;
		moved += move_player(cub3d, delta_x, delta_y);
	}
	return (moved);
}

int	handle_direction(t_cub3d *cub3d)
{
	int		rotated;

	rotated = 0;
	if (cub3d->keys[255])
		rotated = handle_direction_left(cub3d);
	if (cub3d->keys[254])
		rotated += handle_direction_right(cub3d);
	return (rotated);
}

int	handle_direction_left(t_cub3d *cub3d)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub3d->player.dir_x;
	old_plane_x = cub3d->view.plane_x;
	cub3d->player.dir_x = cub3d->player.dir_x * cos(-SENSIBILITY)
		- cub3d->player.dir_y * sin(-SENSIBILITY);
	cub3d->player.dir_y = old_dir_x * sin(-SENSIBILITY)
		+ cub3d->player.dir_y * cos(-SENSIBILITY);
	cub3d->view.plane_x = cub3d->view.plane_x * cos(-SENSIBILITY)
		- cub3d->view.plane_y * sin(-SENSIBILITY);
	cub3d->view.plane_y = old_plane_x * sin(-SENSIBILITY)
		+ cub3d->view.plane_y * cos(-SENSIBILITY);
	return (1);
}

int	handle_direction_right(t_cub3d *cub3d)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub3d->player.dir_x;
	old_plane_x = cub3d->view.plane_x;
	cub3d->player.dir_x = cub3d->player.dir_x * cos(SENSIBILITY)
		- cub3d->player.dir_y * sin(SENSIBILITY);
	cub3d->player.dir_y = old_dir_x * sin(SENSIBILITY)
		+ cub3d->player.dir_y * cos(SENSIBILITY);
	cub3d->view.plane_x = cub3d->view.plane_x * cos(SENSIBILITY)
		- cub3d->view.plane_y * sin(SENSIBILITY);
	cub3d->view.plane_y = old_plane_x * sin(SENSIBILITY)
		+ cub3d->view.plane_y * cos(SENSIBILITY);
	return (1);
}
