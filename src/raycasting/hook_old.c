/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:54:26 by norabino          #+#    #+#             */
/*   Updated: 2025/08/11 19:27:09 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_ESC 65307
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

int	handle_close(t_cub3d *cub3d)
{
	if (!cub3d)
		exit(1);
	if (cub3d->mlx.mlx && cub3d->mlx.win)
		mlx_destroy_window(cub3d->mlx.mlx, cub3d->mlx.win);
	if (cub3d->mlx.img && cub3d->mlx.img->img && cub3d->mlx.mlx)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->mlx.img->img);
	if (cub3d->mlx.mlx)
	{
		mlx_destroy_display(cub3d->mlx.mlx);
		free(cub3d->mlx.mlx);
		cub3d->mlx.mlx = NULL;
	}
	exit_error("closed", cub3d);
	return (0);
}

int	handle_keypress(int keycode, t_cub3d *cub3d)
{
	if (!cub3d)
		return (0);
	if (keycode == KEY_ESC)
		handle_close(cub3d);
	if (keycode < 256)
		cub3d->keys[keycode] = 1;
	else if (keycode == KEY_LEFT)
		cub3d->keys[255] = 1;
	else if (keycode == KEY_RIGHT)
		cub3d->keys[254] = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_cub3d *cub3d)
{
	if (!cub3d)
		return (0);
	if (keycode < 256)
		cub3d->keys[keycode] = 0;
	else if (keycode == KEY_LEFT)
		cub3d->keys[255] = 0;
	else if (keycode == KEY_RIGHT)
		cub3d->keys[254] = 0;
	handle_loop(cub3d);
	return (0);
}

#include "../../includes/cub3d.h"

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_ESC 65307
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

int	handle_close(t_cub3d *cub3d)
{
	if (!cub3d)
		exit(1);
	if (cub3d->mlx.mlx && cub3d->mlx.win)
		mlx_destroy_window(cub3d->mlx.mlx, cub3d->mlx.win);
	if (cub3d->mlx.img && cub3d->mlx.img->img && cub3d->mlx.mlx)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->mlx.img->img);
	if (cub3d->mlx.mlx)
	{
		mlx_destroy_display(cub3d->mlx.mlx);
		free(cub3d->mlx.mlx);
		cub3d->mlx.mlx = NULL;
	}
	exit_error("closed", cub3d);
	return (0);
}

int	handle_keypress(int keycode, t_cub3d *cub3d)
{
	if (!cub3d)
		return (0);
	if (keycode == KEY_ESC)
		handle_close(cub3d);
	if (keycode < 256)
		cub3d->keys[keycode] = 1;
	else if (keycode == KEY_LEFT)
		cub3d->keys[255] = 1;
	else if (keycode == KEY_RIGHT)
		cub3d->keys[254] = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_cub3d *cub3d)
{
	if (!cub3d)
		return (0);
	if (keycode < 256)
		cub3d->keys[keycode] = 0;
	else if (keycode == KEY_LEFT)
		cub3d->keys[255] = 0;
	else if (keycode == KEY_RIGHT)
		cub3d->keys[254] = 0;
	handle_loop(cub3d);
	return (0);
}

int	handle_movement(t_cub3d *cub3d)
{
	double	move_speed;
	double	delta_x;
	double	delta_y;

	if (!cub3d)
		return (0);
	move_speed = 0.02;
	if (cub3d->keys[KEY_W])
	{
		delta_x = cub3d->player.dirX * move_speed;
		delta_y = cub3d->player.dirY * move_speed;
		if (move_player)
			move_player(cub3d, delta_x, delta_y);
		return (1);
	}
	if (cub3d->keys[KEY_S])
	{
		delta_x = -cub3d->player.dirX * move_speed;
		delta_y = -cub3d->player.dirY * move_speed;
		if (move_player)
			move_player(cub3d, delta_x, delta_y);
		return (1);
	}
	return (handle_movement_strafe(cub3d, move_speed));
}

int	handle_movement_strafe(t_cub3d *cub3d, double move_speed)
{
	double	delta_x;
	double	delta_y;

	if (cub3d->keys[KEY_A])
	{
		delta_x = -cub3d->player.dirY * move_speed;
		delta_y = cub3d->player.dirX * move_speed;
		if (move_player)
			move_player(cub3d, delta_x, delta_y);
		return (1);
	}
	if (cub3d->keys[KEY_D])
	{
		delta_x = cub3d->player.dirY * move_speed;
		delta_y = -cub3d->player.dirX * move_speed;
		if (move_player)
			move_player(cub3d, delta_x, delta_y);
		return (1);
	}
	return (0);
}

int	handle_direction(t_cub3d *cub3d)
{
	double	rot_speed;

	if (!cub3d)
		return (0);
	rot_speed = 0.02;
	if (cub3d->keys[255])
	{
		return (handle_direction_left(cub3d, rot_speed));
	}
	if (cub3d->keys[254])
	{
		return (handle_direction_right(cub3d, rot_speed));
	}
	return (0);
}

int	handle_direction_left(t_cub3d *cub3d, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub3d->player.dirX;
	old_plane_x = cub3d->view.planeX;
	cub3d->player.dirX = cub3d->player.dirX * cos(-rot_speed)
		- cub3d->player.dirY * sin(-rot_speed);
	cub3d->player.dirY = old_dir_x * sin(-rot_speed)
		+ cub3d->player.dirY * cos(-rot_speed);
	cub3d->view.planeX = cub3d->view.planeX * cos(-rot_speed)
		- cub3d->view.planeY * sin(-rot_speed);
	cub3d->view.planeY = old_plane_x * sin(-rot_speed)
		+ cub3d->view.planeY * cos(-rot_speed);
	return (1);
}

int	handle_direction_right(t_cub3d *cub3d, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub3d->player.dirX;
	old_plane_x = cub3d->view.planeX;
	cub3d->player.dirX = cub3d->player.dirX * cos(rot_speed)
		- cub3d->player.dirY * sin(rot_speed);
	cub3d->player.dirY = old_dir_x * sin(rot_speed)
		+ cub3d->player.dirY * cos(rot_speed);
	cub3d->view.planeX = cub3d->view.planeX * cos(rot_speed)
		- cub3d->view.planeY * sin(rot_speed);
	cub3d->view.planeY = old_plane_x * sin(rot_speed)
		+ cub3d->view.planeY * cos(rot_speed);
	return (1);
}

int	handle_loop(t_cub3d *cub3d)
{
	int	movement_made;

	if (!cub3d || !cub3d->mlx.mlx || !cub3d->mlx.win || !cub3d->mlx.img)
		return (0);
	movement_made = 0;
	movement_made += handle_movement(cub3d);
	movement_made += handle_direction(cub3d);
	if (movement_made)
	{
		if (cub3d->mlx.img->img)
			mlx_destroy_image(cub3d->mlx.mlx, cub3d->mlx.img->img);
		cub3d->mlx.img->img = mlx_new_image(cub3d->mlx.mlx, 1280, 720);
		if (!cub3d->mlx.img->img)
			return (0);
		cub3d->mlx.img->addr = mlx_get_data_addr(cub3d->mlx.img->img,
				&cub3d->mlx.img->bits_per_pixel,
				&cub3d->mlx.img->line_length, &cub3d->mlx.img->endian);
		raycast(cub3d);
		mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win,
			cub3d->mlx.img->img, 0, 0);
	}
	return (0);
}
