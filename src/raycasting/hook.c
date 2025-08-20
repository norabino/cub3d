/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:54:26 by norabino          #+#    #+#             */
/*   Updated: 2025/08/20 15:36:44 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_close(t_cub3d *cub3d)
{
	if (!cub3d)
		exit(1);
	ft_free(cub3d);
	exit(0);
	return (0);
}

int	handle_keypress(int keycode, t_cub3d *cub3d)
{
	if (!cub3d)
		return (0);
	if (keycode == KEY_ESC)
		handle_close(cub3d);
	if (keycode < 256)
		cub3d->keys[keycode] = 1;
	else if (keycode == KEY_LEFT)
		cub3d->keys[255] = 1;
	else if (keycode == KEY_RIGHT)
		cub3d->keys[254] = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_cub3d *cub3d)
{
	if (!cub3d)
		return (0);
	if (keycode < 256)
		cub3d->keys[keycode] = 0;
	else if (keycode == KEY_LEFT)
		cub3d->keys[255] = 0;
	else if (keycode == KEY_RIGHT)
		cub3d->keys[254] = 0;
	return (0);
}
