/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_collect_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:46:46 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/16 16:17:14 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	check_map_bounds(t_cub3d *cub3d, double x, double y)
{
	if (x < 0 || y < 0)
		return (1);
	if ((int)y >= ft_tablen(cub3d->map))
		return (1);
	if ((int)x >= (int)ft_strlen(cub3d->map[(int)y]))
		return (1);
	return (0);
}

int	is_wall_at_position(t_cub3d *cub3d, double x, double y)
{
	char	cell;

	if (check_map_bounds(cub3d, x, y))
		return (1);
	cell = cub3d->map[(int)y][(int)x];
	return (cell == '1');
}
