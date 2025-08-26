/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:31:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/26 19:07:51 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Boucle principale du jeu qui s'exécute en continu
** Comme le cœur qui bat régulièrement pour faire vivre le corps
** Met à jour les mouvements, la vue et l'affichage
*/
int	handle_loop(t_cub3d *cub3d)
{
	if (!cub3d || !cub3d->mlx.mlx || !cub3d->mlx.win || !cub3d->mlx.img)
		return (0);
	if (limit_fps(cub3d))
	{
		update_delta_time(cub3d);
		handle_movement(cub3d);
		handle_direction(cub3d);
		check_any_key_pressed(cub3d);
		cub3d->last_refresh = gettime_ms();
		calculate_fps(cub3d);
		refresh_image(cub3d);
	}
	return (0);
}

/*
** Vérifie si une touche du clavier est actuellement pressée
** Comme regarder si quelqu'un appuie sur un bouton
** pour savoir si on doit faire quelque chose
*/
int	check_any_key_pressed(t_cub3d *cub3d)
{
	int	i;

	if (!cub3d)
		return (0);
	i = 0;
	while (i < 256)
	{
		if (cub3d->keys[i])
			return (1);
		i++;
	}
	return (0);
}

/*
** Rafraîchit l'image à l'écran
** Comme repeindre un tableau à chaque fois qu'on change quelque chose
** pour que l'écran montre toujours la bonne image
*/
void	refresh_image(t_cub3d *cub3d)
{
	if (!cub3d || !cub3d->mlx.mlx || !cub3d->mlx.win || !cub3d->mlx.img)
		return ;
	if (!cub3d->mlx.img->img)
		return ;
	raycast(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win,
		cub3d->mlx.img->img, 0, 0);
	display_fps(cub3d);
}
