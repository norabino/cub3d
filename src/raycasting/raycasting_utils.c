/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/08/22 15:22:52 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Prépare les paramètres de base pour l'algorithme DDA
** DDA = méthode mathématique pour suivre une ligne droite sur une grille
** Comme préparer une règle et un compas avant de tracer une ligne droite
*/
void	init_dda_params(t_cub3d *cub3d, double ray_dir_x, double ray_dir_y,
	t_dda *dda)
{
	if (!dda)
		return ;
	dda->map_x = (int)cub3d->player.pos_x;
	dda->map_y = (int)cub3d->player.pos_y;
	if (ray_dir_x == 0)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = ft_abs(1.0 / ray_dir_x);
	if (ray_dir_y == 0)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = ft_abs(1.0 / ray_dir_y);
	dda->hit = 0;
}

/*
** Calcule dans quelle direction avancer et les distances initiales
** Détermine si on va vers la droite/gauche et haut/bas
** Prépare les mesures pour savoir quand on atteint le prochain mur
*/
void	init_step_and_side_dist(t_dda *dda, double ray_dir_x,
	double ray_dir_y, t_cub3d *cub3d)
{
	int	map_x;

	map_x = (int)cub3d->player.pos_x;
	if (ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (cub3d->player.pos_x - map_x)
			* dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (map_x + 1 - cub3d->player.pos_x)
			* dda->delta_dist_x;
	}
	init_step_and_side_dist_y(dda, ray_dir_y, cub3d);
}

/*
** Fonction d'aide pour init_step_and_side_dist (direction Y - verticale)
** Calcule spécifiquement comment avancer vers le haut ou le bas
** Séparée de la direction X pour respecter la limite de 25 lignes
*/
void	init_step_and_side_dist_y(t_dda *dda, double ray_dir_y,
	t_cub3d *cub3d)
{
	int	map_y;

	map_y = (int)cub3d->player.pos_y;
	if (ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (cub3d->player.pos_y - map_y)
			* dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (map_y + 1.0 - cub3d->player.pos_y)
			* dda->delta_dist_y;
	}
}

/*
** Exécute l'algorithme DDA pour trouver où le rayon touche un mur
** DDA = avance case par case sur la grille jusqu'à toucher un mur
** Comme un jeu de l'oie : on avance case par case jusqu'à l'obstacle
** La limite de 1000 évite les boucles infinies
*/
void	perform_dda_algorithm(t_cub3d *cub3d, t_dda *dda)
{
	int	max_iterations;

	if (!cub3d->map)
		return ;
	max_iterations = 1000;
	while (dda->hit == 0 && max_iterations-- > 0)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (dda->map_y >= 0 && dda->map_x >= 0
			&& cub3d->map[(int)dda->map_y]
			&& cub3d->map[(int)dda->map_y][(int)dda->map_x] == '1')
			dda->hit = 1;
	}
}

/*
** Calcule la distance exacte perpendiculaire jusqu'au mur
** Perpendiculaire = distance la plus courte, en ligne droite
** Important pour éviter l'effet "fish-eye" (déformation de poisson)
** Plus technique : corrige la distance pour qu'elle soit toujours mesurée
** perpendiculairement à l'écran, pas en diagonale
*/
double	calc_perpendicular_wall_distance(t_dda *dda, double ray_dir_x,
	double ray_dir_y, t_cub3d *cub3d)
{
	double	perp_wall_dist;

	if (dda->side == 0)
	{
		perp_wall_dist = (dda->map_x - cub3d->player.pos_x
				+ (1 - dda->step_x) / 2) / ray_dir_x;
	}
	else
	{
		perp_wall_dist = (dda->map_y - cub3d->player.pos_y
				+ (1 - dda->step_y) / 2) / ray_dir_y;
	}
	return (ft_abs(perp_wall_dist));
}
