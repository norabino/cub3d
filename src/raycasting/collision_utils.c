/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:30:00 by norabino          #+#    #+#             */
/*   Updated: 2025/08/26 19:07:51 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Vérifie les collisions aux coins supérieurs du joueur
** Comme vérifier si les épaules ne touchent pas les murs
** quand on passe dans un couloir étroit
*/
int	check_corner_positions(t_cub3d *cub3d, double x, double y)
{
	if (cub3d->map[(int)(y - COLLISION_MARGIN)] == NULL ||
		cub3d->map[(int)(y - COLLISION_MARGIN)][(int)(x - COLLISION_MARGIN)]
		== '\0' ||
		cub3d->map[(int)(y - COLLISION_MARGIN)][(int)(x - COLLISION_MARGIN)]
		== '1')
		return (0);
	if (cub3d->map[(int)(y - COLLISION_MARGIN)] == NULL ||
		cub3d->map[(int)(y - COLLISION_MARGIN)][(int)(x + COLLISION_MARGIN)]
		== '\0' ||
		cub3d->map[(int)(y - COLLISION_MARGIN)][(int)(x + COLLISION_MARGIN)]
		== '1')
		return (0);
	return (1);
}

/*
** Vérifie les collisions aux coins inférieurs du joueur
** Comme vérifier si les pieds ne touchent pas les murs
** en bas quand on se déplace
*/
int	check_bottom_corners(t_cub3d *cub3d, double x, double y)
{
	if (cub3d->map[(int)(y + COLLISION_MARGIN)] == NULL ||
		cub3d->map[(int)(y + COLLISION_MARGIN)][(int)(x - COLLISION_MARGIN)]
		== '\0' ||
		cub3d->map[(int)(y + COLLISION_MARGIN)][(int)(x - COLLISION_MARGIN)]
		== '1')
		return (0);
	if (cub3d->map[(int)(y + COLLISION_MARGIN)] == NULL ||
		cub3d->map[(int)(y + COLLISION_MARGIN)][(int)(x + COLLISION_MARGIN)]
		== '\0' ||
		cub3d->map[(int)(y + COLLISION_MARGIN)][(int)(x + COLLISION_MARGIN)]
		== '1')
		return (0);
	return (1);
}
