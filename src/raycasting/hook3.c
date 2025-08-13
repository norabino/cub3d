/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:31:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/13 16:54:00 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_loop(t_cub3d *cub3d)
{
	int	movement_occurred;
	int	rotation_occurred;
	int	key_pressed;

	if (!cub3d || !cub3d->mlx.mlx || !cub3d->mlx.win || !cub3d->mlx.img)
		return (0);
	movement_occurred = handle_movement(cub3d);
	rotation_occurred = handle_direction(cub3d);
	key_pressed = check_any_key_pressed(cub3d);
	if (movement_occurred || rotation_occurred || key_pressed)
		refresh_image(cub3d);
	return (0);
}

int	check_any_key_pressed(t_cub3d *cub3d)
{
	int	i;

	if (!cub3d)
		return (0);
	i = 0;
	while (i < 256)
	{
		if (cub3d->keys[i])
			return (1);
		i++;
	}
	if (cub3d->keys[254] || cub3d->keys[255])
		return (1);
	return (0);
}

void	refresh_image(t_cub3d *cub3d)
{
	if (!cub3d || !cub3d->mlx.mlx || !cub3d->mlx.win || !cub3d->mlx.img)
		return ;
	if (!cub3d->mlx.img->img)
		return ;
	raycast(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win,
		cub3d->mlx.img->img, 0, 0);
}
