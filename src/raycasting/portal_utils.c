/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:25:18 by norabino          #+#    #+#             */
/*   Updated: 2025/09/09 23:36:18 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdint.h>

/* Met à jour les animations des portails */
void	update_portal_animations(t_cub3d *cub3d)
{
	int		i;
	long	current_time;
	long	frame_duration;

	if (!cub3d || !cub3d->tp_portals || cub3d->nb_portals <= 0)
		return ;
	current_time = gettime_ms();
	frame_duration = 1000 / FPS;
	i = 0;
	while (i < cub3d->nb_portals)
	{
		if ((current_time - cub3d->prtl_sprites.last_frame_time)
			>= frame_duration)
		{
			cub3d->prtl_sprites.current_frame
				= (cub3d->prtl_sprites.current_frame + 1) % 16;
			cub3d->prtl_sprites.last_frame_time = current_time;
			cub3d->prtl_sprites.frame_counter++;
		}
		i++;
	}
}

/* Libère la mémoire des sprites de portails */
void	free_portal_sprites(t_cub3d *cub3d)
{
	int	i;
	int	frame_count_save;

	if (!cub3d)
		return ;
	
	frame_count_save = cub3d->prtl_sprites.frame_counter;
	
	// Libérer les frames de texture (sans détruire les images MLX)
	if (cub3d->prtl_sprites.frames && frame_count_save > 0)
	{
		// NOTE: On ne détruit pas les images MLX car cela peut causer des segfaults
		// lors de la fermeture du programme. MLX s'occupe de les nettoyer automatiquement.
		free(cub3d->prtl_sprites.frames);
		cub3d->prtl_sprites.frames = NULL;
	}
	
	// Libérer les paths
	if (cub3d->prtl_sprites.path && frame_count_save > 0)
	{
		i = 0;
		while (i < frame_count_save && cub3d->prtl_sprites.path[i])
		{
			free(cub3d->prtl_sprites.path[i]);
			cub3d->prtl_sprites.path[i] = NULL;
			i++;
		}
		free(cub3d->prtl_sprites.path);
		cub3d->prtl_sprites.path = NULL;
	}
	
	// Remettre à zéro les compteurs
	cub3d->prtl_sprites.frame_counter = 0;
	cub3d->prtl_sprites.current_frame = 0;
	
	// Libérer les portails
	if (cub3d->tp_portals)
	{
		free(cub3d->tp_portals);
		cub3d->tp_portals = NULL;
	}
}
