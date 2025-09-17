/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:40:54 by norabino          #+#    #+#             */
/*   Updated: 2025/09/17 22:17:19 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Valide toutes les couleurs du fichier de configuration */
int	validate_all_colors(t_cub3d *cub3d, int *idx)
{
	int	i;
	int	result;

	i = 0;
	*idx = 0;
	while (cub3d->file[i])
	{
		result = process_color_line(cub3d, i);
		if (result != -1)
			*idx = result;
		i++;
	}
	validate_colors_complete(cub3d);
	return (1);
}

/* Vérifie si toutes les couleurs sont définies */
int	all_colors_set(t_cub3d *cub3d)
{
	int	ceiling_complete;
	int	floor_complete;

	ceiling_complete = (cub3d->textures.ceiling)
		|| (cub3d->colors.ceiling[0] != -1
			&& cub3d->colors.ceiling[1] != -1
			&& cub3d->colors.ceiling[2] != -1);
	floor_complete = (cub3d->textures.floor)
		|| (cub3d->colors.floor[0] != -1
			&& cub3d->colors.floor[1] != -1
			&& cub3d->colors.floor[2] != -1);
	return (ceiling_complete && floor_complete);
}

/* Définit la couleur du plafond */
void	set_ceiling(t_cub3d *cub3d, char **split)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		if (i >= 3)
			exit_error("Invalid RGB ceiling nbs, must be 3", cub3d);
		cub3d->colors.ceiling[i] = ft_atoi(split[i]);
		if (cub3d->colors.ceiling[i] < 0 || cub3d->colors.ceiling[i] > 255)
			exit_error("Wrong ceiling color args [0-255]", cub3d);
	}
}

/* Définit la couleur du sol */
void	set_floor(t_cub3d *cub3d, char **split)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		if (ft_tablen(split) != 3)
			exit_error("Invalid RGB floor nbs, must be 3", cub3d);
		cub3d->colors.floor[i] = ft_atoi(split[i]);
		if (cub3d->colors.floor[i] < 0 || cub3d->colors.floor[i] > 255)
			exit_error("Wrong floor color args [0-255]", cub3d);
	}
}
