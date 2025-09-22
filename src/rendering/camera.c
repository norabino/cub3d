/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/22 16:32:03 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calc_camera_plane(t_cub3d *cub3d)
{
	double	fov_rad;

	if (!cub3d)
		return ;
	fov_rad = FOV * PI / 180.0;
	cub3d->view.plane_x = -cub3d->player.dir_y * tan(fov_rad / 2.0);
	cub3d->view.plane_y = cub3d->player.dir_x * tan(fov_rad / 2.0);
}
