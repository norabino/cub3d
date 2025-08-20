/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/08/20 15:28:20 by jdupuis          ###   ########.fr       */
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
	cub3d->view.plane_x = -cub3d->player.dir_y * tan(fov_rad / 2.0);
	cub3d->view.plane_y = cub3d->player.dir_x * tan(fov_rad / 2.0);
}
