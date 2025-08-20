/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:30:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/20 15:46:14 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_movement(t_cub3d *cub3d)
{
	double	move_speed;
	double	delta_x;
	double	delta_y;
	int		moved;

	if (!cub3d)
		return (0);
	move_speed = 0.02;
	moved = 0;
	if (cub3d->keys[KEY_W])
	{
		delta_x = cub3d->player.dir_x * move_speed;
		delta_y = cub3d->player.dir_y * move_speed;
		moved += move_player(cub3d, delta_x, delta_y);
	}
	if (cub3d->keys[KEY_S])
	{
		delta_x = -cub3d->player.dir_x * move_speed;
		delta_y = -cub3d->player.dir_y * move_speed;
		moved += move_player(cub3d, delta_x, delta_y);
	}
	return (moved + handle_movement_strafe(cub3d, move_speed));
}

int	handle_movement_strafe(t_cub3d *cub3d, double move_speed)
{
	double	delta_x;
	double	delta_y;
	int		moved;

	moved = 0;
	if (cub3d->keys[KEY_A])
	{
		delta_x = cub3d->player.dir_y * move_speed;
		delta_y = -cub3d->player.dir_x * move_speed;
		moved += move_player(cub3d, delta_x, delta_y);
	}
	if (cub3d->keys[KEY_D])
	{
		delta_x = -cub3d->player.dir_y * move_speed;
		delta_y = cub3d->player.dir_x * move_speed;
		moved += move_player(cub3d, delta_x, delta_y);
	}
	return (moved);
}

int	handle_direction(t_cub3d *cub3d)
{
	double	rot_speed;
	int		rotated;

	if (!cub3d)
		return (0);
	rot_speed = 0.03;
	rotated = 0;
	if (cub3d->keys[255])
		rotated = handle_direction_left(cub3d, rot_speed);
	if (cub3d->keys[254])
		rotated += handle_direction_right(cub3d, rot_speed);
	return (rotated);
}

int	handle_direction_left(t_cub3d *cub3d, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub3d->player.dir_x;
	old_plane_x = cub3d->view.plane_x;
	cub3d->player.dir_x = cub3d->player.dir_x * cos(-rot_speed)
		- cub3d->player.dir_y * sin(-rot_speed);
	cub3d->player.dir_y = old_dir_x * sin(-rot_speed)
		+ cub3d->player.dir_y * cos(-rot_speed);
	cub3d->view.plane_x = cub3d->view.plane_x * cos(-rot_speed)
		- cub3d->view.plane_y * sin(-rot_speed);
	cub3d->view.plane_y = old_plane_x * sin(-rot_speed)
		+ cub3d->view.plane_y * cos(-rot_speed);
	return (1);
}

int	handle_direction_right(t_cub3d *cub3d, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub3d->player.dir_x;
	old_plane_x = cub3d->view.plane_x;
	cub3d->player.dir_x = cub3d->player.dir_x * cos(rot_speed)
		- cub3d->player.dir_y * sin(rot_speed);
	cub3d->player.dir_y = old_dir_x * sin(rot_speed)
		+ cub3d->player.dir_y * cos(rot_speed);
	cub3d->view.plane_x = cub3d->view.plane_x * cos(rot_speed)
		- cub3d->view.plane_y * sin(rot_speed);
	cub3d->view.plane_y = old_plane_x * sin(rot_speed)
		+ cub3d->view.plane_y * cos(rot_speed);
	return (1);
}
