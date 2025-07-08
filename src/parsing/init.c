/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:24:01 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/08 14:08:45 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init(t_cub3d *cub3d)
{
	cub3d->textures.north = NULL;
	cub3d->textures.south = NULL;
	cub3d->textures.west = NULL;
	cub3d->textures.east = NULL;
	cub3d->colors.floor[0] = -1;
	cub3d->colors.floor[1] = -1;
	cub3d->colors.floor[2] = -1;
	cub3d->colors.ceiling[0] = -1;
	cub3d->colors.ceiling[1] = -1;
	cub3d->colors.ceiling[1] = -1;
	cub3d->map = NULL;
}
