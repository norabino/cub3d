/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:31:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/25 13:32:19 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_loop(t_cub3d *cub3d)
{
	/*int	movement_occurred;
	int	rotation_occurred;
	int	key_pressed;*/
	double	n;
	int	fps;

	if (!cub3d || !cub3d->mlx.mlx || !cub3d->mlx.win || !cub3d->mlx.img)
		return (0);
	handle_movement(cub3d);
	handle_direction(cub3d);
	check_any_key_pressed(cub3d);
	fps = 0;
	if (check_frames(cub3d))
	{
		cub3d->last_refresh = gettime_ms();
		refresh_image(cub3d);
		printf("time : %ld\n", (gettime_ms() / 1000));
		n = gettime_ms() / 1000;
		if (n == (gettime_ms() / 1000))
		{
			printf("fps : %d", fps++);
		}
		else
			fps = 0;
	}
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
