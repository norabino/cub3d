/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:54:26 by norabino          #+#    #+#             */
/*   Updated: 2025/08/20 16:05:01 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Gère la fermeture du programme (bouton X de la fenêtre)
** Nettoie la mémoire et ferme proprement le programme
*/
int	handle_close(t_cub3d *cub3d)
{
	if (!cub3d)
		exit(1);
	ft_free(cub3d);
	exit(0);
	return (0);
}

/*
** Gère l'appui sur une touche du clavier
** Enregistre quelle touche est pressée pour l'utiliser plus tard
** ESC = quitter, flèches = rotation, WASD = mouvement
*/
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

/*
** Gère le relâchement d'une touche du clavier
** Marque la touche comme "non pressée" quand on la lâche
** Important pour arrêter le mouvement quand on lâche WASD
*/
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
