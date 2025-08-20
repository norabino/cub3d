/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:30:00 by norabino          #+#    #+#             */
/*   Updated: 2025/08/20 16:05:01 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Vérifie si une position est valide (pas un mur) avec une marge de sécurité
** Comme vérifier si on peut marcher à un endroit sans se cogner
** La marge de 0.05 évite que le joueur colle aux murs
** Retourne 1 si on peut aller là, 0 si c'est bloqué
*/
int	is_valid_position(t_cub3d *cub3d, double x, double y)
{
	if (!cub3d || !cub3d->map)
		return (0);
	if (x < 0.05 || y < 0.05)
		return (0);
	if (cub3d->map[(int)y] == NULL)
		return (0);
	if (cub3d->map[(int)y][(int)x] == '\0')
		return (0);
	if (cub3d->map[(int)y][(int)x] == '1')
		return (0);
	return (1);
}

/*
** Déplace le joueur en vérifiant les collisions
** Teste la nouvelle position avant de s'y déplacer
** Si ça passe, on bouge. Si ça coince, on reste sur place
** Retourne 1 si le mouvement a eu lieu, 0 sinon
*/
int	move_player(t_cub3d *cub3d, double delta_x, double delta_y)
{
	double	new_x;
	double	new_y;

	if (!cub3d)
		return (0);
	new_x = cub3d->player.pos_x + delta_x;
	new_y = cub3d->player.pos_y + delta_y;
	if (is_valid_position(cub3d, new_x, cub3d->player.pos_y)
		&& is_valid_position(cub3d, cub3d->player.pos_x, new_y))
	{
		cub3d->player.pos_x = new_x;
		cub3d->player.pos_y = new_y;
		return (1);
	}
	return (0);
}
