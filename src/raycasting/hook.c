/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:54:26 by norabino          #+#    #+#             */
/*   Updated: 2025/07/30 15:57:31 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_close(t_cub3d *cub3d)
{
	if (cub3d->mlx.mlx && cub3d->mlx.win)
		mlx_destroy_window(cub3d->mlx.mlx, cub3d->mlx.win);
	if (cub3d->mlx.img && cub3d->mlx.img->img)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->mlx.img->img);
	if (cub3d->mlx.mlx)
	{
		mlx_destroy_display(cub3d->mlx.mlx);
		cub3d->mlx.mlx = NULL;
	}
	exit_error("closed", cub3d);
	return (0);
}

void	handle_keycode(int key, t_cub3d *cub3d)
{
	if (key == 35307 || key == 65307)
		handle_close(cub3d);
	
}

int	handle_hook(int keycode, t_cub3d *cub3d)
{
	handle_keycode(keycode, cub3d);
	if (cub3d->mlx.img && cub3d->mlx.img->img)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->mlx.img->img);
	cub3d->mlx.img->img = mlx_new_image(cub3d->mlx.mlx, 1280, 720);
	if (!cub3d->mlx.img->img)
		exit_error("no img", cub3d);
	cub3d->mlx.img->addr = mlx_get_data_addr(cub3d->mlx.img->img, &cub3d->mlx.img->bits_per_pixel,
			&cub3d->mlx.img->line_length, &cub3d->mlx.img->endian);
	//cub3d_draw(cub3d);
	return (0);
}