/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/08/13 15:27:44 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Calculate camera plane based on field of view */
void	calc_camera_plane(t_cub3d *cub3d)
{
	double	fov_rad;

	if (!cub3d)
		return ;
	fov_rad = cub3d->player.fov * PI / 180.0;
	cub3d->view.planeX = -cub3d->player.dirY * tan(fov_rad / 2.0);
	cub3d->view.planeY = cub3d->player.dirX * tan(fov_rad / 2.0);
}
