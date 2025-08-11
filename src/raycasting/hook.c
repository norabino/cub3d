/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:54:26 by norabino          #+#    #+#             */
/*   Updated: 2025/08/11 19:45:25 by norabino         ###   ########.fr       */
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
