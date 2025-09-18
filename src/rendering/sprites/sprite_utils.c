/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 20:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/18 20:14:47 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/* Update z-buffer for depth testing */
void	update_depth_buffer(t_cub3d *cub3d, int x, double distance)
{
	if (x >= 0 && x < SCREEN_WIDTH && distance < cub3d->depth_buffer.buffer[x])
		cub3d->depth_buffer.buffer[x] = distance;
}
