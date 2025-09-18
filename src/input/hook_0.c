/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:54:26 by norabino          #+#    #+#             */
/*   Updated: 2025/09/18 17:47:57 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Gère la fermeture du programme (bouton X de la fenêtre) */
int	handle_close(t_cub3d *cub3d)
{
	ft_free(cub3d);
	exit(0);
	return (0);
}

/* Gère l'appui sur une touche du clavier */
int	handle_keypress(int keycode, t_cub3d *cub3d)
{
	if (keycode == KEY_ESC)
		handle_close(cub3d);
	if (keycode < 256)
		cub3d->input_state[keycode] = 1;
	else if (keycode == KEY_LEFT)
		cub3d->input_state[255] = 1;
	else if (keycode == KEY_RIGHT)
		cub3d->input_state[254] = 1;
	return (0);
}

/* Gère le relâchement d'une touche du clavier */
int	handle_keyrelease(int keycode, t_cub3d *cub3d)
{
	if (keycode < 256)
		cub3d->input_state[keycode] = 0;
	else if (keycode == KEY_LEFT)
		cub3d->input_state[255] = 0;
	else if (keycode == KEY_RIGHT)
		cub3d->input_state[254] = 0;
	return (0);
}
