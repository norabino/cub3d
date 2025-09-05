/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_alpha.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:00:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/05 02:14:28 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Lit la couleur d'un pixel existant dans l'image */
int	get_pixel_color(t_img *img, int x, int y)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return (0x000000);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

/* Applique un alpha blending entre deux couleurs */
int	alpha_blend(int bg_color, int fg_color, double alpha)
{
	int	alpha_int;
	int	inv_alpha;
	int	result;

	alpha_int = (int)(alpha * 256);
	inv_alpha = 256 - alpha_int;
	result = blend_color_component(bg_color, fg_color, alpha_int, inv_alpha);
	return (result);
}

/* Calcule la largeur pour une ligne donnée du triangle */
static int	get_triangle_width_for_row(int y)
{
	int	row_index;

	if (y < -9 || y > 0)
		return (0);
	row_index = y + 9;
	if (row_index == 0 || row_index == 1)
		return (1);
	else if (row_index == 2 || row_index == 3)
		return (3);
	else if (row_index == 4 || row_index == 5)
		return (5);
	else if (row_index == 6 || row_index == 7)
		return (7);
	else
		return (9);
}

/* Vérifie si le pixel fait partie de la forme de la flèche */
int	is_arrow_pixel(int x, int y)
{
	int	triangle_width;
	int	half_width;

	triangle_width = get_triangle_width_for_row(y);
	if (triangle_width == 0)
		return (0);
	half_width = triangle_width / 2;
	return (x >= -half_width && x <= half_width);
}

/* Vérifie si le pixel fait partie du contour noir */
int	is_arrow_border(int x, int y)
{
	int	triangle_width;
	int	half_width;

	triangle_width = get_triangle_width_for_row(y);
	if (triangle_width == 0)
		return (0);
	half_width = triangle_width / 2;
	if (y == 0)
		return (x >= -half_width && x <= half_width);
	return (x == -half_width || x == half_width);
}
