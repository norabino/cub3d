/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 20:00:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/18 20:54:52 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Nettoyage d'urgence en cas d'erreur pendant l'initialisation */
void	emergency_cleanup(t_cub3d *cub3d)
{
	if (!cub3d)
		return ;
	if (cub3d->file)
		free_map(cub3d->file);
	if (cub3d->map)
		free_map(cub3d->map);
	if (cub3d->invalid_arg)
		secure_free((void **)&cub3d->invalid_arg);
	if (cub3d->tp_portals)
		secure_free((void **)&cub3d->tp_portals);
	if (cub3d->sprites)
		secure_free((void **)&cub3d->sprites);
}

/* Vérification de sécurité pour éviter les doubles free */
int	is_valid_pointer(void *ptr)
{
	if (!ptr)
		return (0);
	return (1);
}
