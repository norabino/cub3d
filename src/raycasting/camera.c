/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/08/22 15:05:18 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Calcule le plan de la caméra selon le champ de vision (FOV)
** Le plan de la caméra détermine la largeur de vision
** Plus le FOV est grand, plus on voit large (comme un objectif grand angle)
** C'est ce qui transforme l'angle de vision en coordonnées pour les rayons
*/
void	calc_camera_plane(t_cub3d *cub3d)
{
	double	fov_rad;

	if (!cub3d)
		return ;
	fov_rad = cub3d->player.fov * PI / 180.0;
	cub3d->view.plane_x = -cub3d->player.dir_y * tan(fov_rad / 2.0);
	cub3d->view.plane_y = cub3d->player.dir_x * tan(fov_rad / 2.0);
}
