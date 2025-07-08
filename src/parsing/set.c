/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:24:01 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/08 11:35:18 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	set_textures(t_textures *textures, char **file)
{
	textures->north = file[0];
	textures->south = file[1];
	textures->west = file[2];
	textures->east = file[3];
}

int	set_colors(t_colors *colors, char **file)
{
	colors->floor[0] = 0;
	colors->floor[1] = 0;
	colors->floor[2] = 0;
	colors->ceiling[0] = 0;
	colors->ceiling[0] = 0;
}

int	set_cub(t_cubed *cubed, char **file)
{
	set_textures(&cubed->textures, file);
	set_colors(cubed->colors, file);
	set_map(cubed->mapn file);
}

