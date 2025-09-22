/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:30:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/22 18:53:30 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_movement(t_cub3d *cub3d)
{
	double	delta_x;
	double	delta_y;
	double	frame_speed;
	int		moved;

	moved = 0;
	frame_speed = MOVE_SPEED * cub3d->time.delta_time;
	if (cub3d->input_state[KEY_W])
	{
		delta_x = cub3d->player.dir_x * frame_speed;
		delta_y = cub3d->player.dir_y * frame_speed;
		moved += move_player(cub3d, delta_x, delta_y);
	}
	if (cub3d->input_state[KEY_S])
	{
		delta_x = -cub3d->player.dir_x * frame_speed;
		delta_y = -cub3d->player.dir_y * frame_speed;
		moved += move_player(cub3d, delta_x, delta_y);
	}
	return (moved + handle_movement_strafe(cub3d));
}

int	handle_movement_strafe(t_cub3d *cub3d)
{
	double	delta_x;
	double	delta_y;
	double	frame_speed;
	int		moved;

	moved = 0;
	frame_speed = MOVE_SPEED * cub3d->time.delta_time;
	if (cub3d->input_state[KEY_A])
	{
		delta_x = cub3d->player.dir_y * frame_speed;
		delta_y = -cub3d->player.dir_x * frame_speed;
		moved += move_player(cub3d, delta_x, delta_y);
	}
	if (cub3d->input_state[KEY_D])
	{
		delta_x = -cub3d->player.dir_y * frame_speed;
		delta_y = cub3d->player.dir_x * frame_speed;
		moved += move_player(cub3d, delta_x, delta_y);
	}
	return (moved);
}

int	handle_direction(t_cub3d *cub3d)
{
	int		rotated;

	rotated = 0;
	if (cub3d->input_state[255])
		rotated = handle_direction_left(cub3d);
	if (cub3d->input_state[254])
		rotated += handle_direction_right(cub3d);
	return (rotated);
}

int	handle_direction_left(t_cub3d *cub3d)
{
	double	old_dir_x;
	double	old_plane_x;
	double	frame_sensitivity;

	frame_sensitivity = SENSIBILITY * cub3d->time.delta_time;
	old_dir_x = cub3d->player.dir_x;
	old_plane_x = cub3d->view.plane_x;
	cub3d->player.dir_x = cub3d->player.dir_x * cos(-frame_sensitivity)
		- cub3d->player.dir_y * sin(-frame_sensitivity);
	cub3d->player.dir_y = old_dir_x * sin(-frame_sensitivity)
		+ cub3d->player.dir_y * cos(-frame_sensitivity);
	cub3d->view.plane_x = cub3d->view.plane_x * cos(-frame_sensitivity)
		- cub3d->view.plane_y * sin(-frame_sensitivity);
	cub3d->view.plane_y = old_plane_x * sin(-frame_sensitivity)
		+ cub3d->view.plane_y * cos(-frame_sensitivity);
	return (1);
}

int	handle_direction_right(t_cub3d *cub3d)
{
	double	old_dir_x;
	double	old_plane_x;
	double	frame_sensitivity;

	frame_sensitivity = SENSIBILITY * cub3d->time.delta_time;
	old_dir_x = cub3d->player.dir_x;
	old_plane_x = cub3d->view.plane_x;
	cub3d->player.dir_x = cub3d->player.dir_x * cos(frame_sensitivity)
		- cub3d->player.dir_y * sin(frame_sensitivity);
	cub3d->player.dir_y = old_dir_x * sin(frame_sensitivity)
		+ cub3d->player.dir_y * cos(frame_sensitivity);
	cub3d->view.plane_x = cub3d->view.plane_x * cos(frame_sensitivity)
		- cub3d->view.plane_y * sin(frame_sensitivity);
	cub3d->view.plane_y = old_plane_x * sin(frame_sensitivity)
		+ cub3d->view.plane_y * cos(frame_sensitivity);
	return (1);
}
