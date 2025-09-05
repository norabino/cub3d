/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:30:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/05 02:14:28 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Vérifie les collisions aux coins supérieurs du joueur */
/* Vérifie les positions des coins pour la collision */
int	check_corner_positions(t_cub3d *cub3d, double x, double y)
{
	int		margin_y;
	int		left_x;
	int		right_x;
	char	left_char;
	char	right_char;

	margin_y = (int)(y - COLLISION_MARGIN);
	left_x = (int)(x - COLLISION_MARGIN);
	right_x = (int)(x + COLLISION_MARGIN);
	left_char = safe_map_access(cub3d, margin_y, left_x);
	right_char = safe_map_access(cub3d, margin_y, right_x);
	if (left_char == '1' || right_char == '1')
		return (0);
	return (1);
}

/* Vérifie les collisions aux coins inférieurs du joueur */
/* Vérifie les coins inférieurs pour la collision */
int	check_bottom_corners(t_cub3d *cub3d, double x, double y)
{
	int		margin_y;
	int		left_x;
	int		right_x;
	char	left_char;
	char	right_char;

	margin_y = (int)(y + COLLISION_MARGIN);
	left_x = (int)(x - COLLISION_MARGIN);
	right_x = (int)(x + COLLISION_MARGIN);
	left_char = safe_map_access(cub3d, margin_y, left_x);
	right_char = safe_map_access(cub3d, margin_y, right_x);
	if (left_char == '1' || right_char == '1')
		return (0);
	return (1);
}
