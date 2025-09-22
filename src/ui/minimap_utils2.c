/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:00:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/22 18:04:05 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_triangle_width_for_row(int y)
{
	int	row_index;

	if (y < -9 || y > 0)
		return (0);
	row_index = y + 9;
	if (row_index == 0 || row_index == 1)
		return (1);
	if (row_index == 2 || row_index == 3)
		return (3);
	if (row_index == 4 || row_index == 5)
		return (5);
	if (row_index == 6 || row_index == 7)
		return (7);
	return (9);
}

int	is_arrow_border(int x, int y)
{
	int	triangle_width;
	int	half_width;

	triangle_width = get_triangle_width_for_row(y);
	if (triangle_width == 0)
		return (0);
	half_width = triangle_width / 2;
	if (y == 0)
	{
		if (x >= -half_width)
			if (x <= half_width)
				return (1);
		return (0);
	}
	if (x == -half_width)
		return (1);
	if (x == half_width)
		return (1);
	return (0);
}
