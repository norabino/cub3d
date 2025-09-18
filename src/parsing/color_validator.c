/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:40:54 by norabino          #+#    #+#             */
/*   Updated: 2025/09/18 16:10:22 by norabino         ###   ########.fr       */
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

/* Définit la couleur du plafond */
void	set_ceiling(t_cub3d *cub3d, char **split)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		if (i >= 3)
		{
			free_map(split);
			exit_error("Invalid RGB ceiling nbs, must be 3", cub3d);
		}
		cub3d->colors.ceiling[i] = ft_atoi(split[i]);
		if (cub3d->colors.ceiling[i] < 0 || cub3d->colors.ceiling[i] > 255)
		{
			free_map(split);
			exit_error("Wrong ceiling color args [0-255]", cub3d);
		}
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
		{
			free_map(split);
			exit_error("Invalid RGB floor nbs, must be 3", cub3d);
		}
		cub3d->colors.floor[i] = ft_atoi(split[i]);
		if (cub3d->colors.floor[i] < 0 || cub3d->colors.floor[i] > 255)
		{
			free_map(split);
			exit_error("Wrong floor color args [0-255]", cub3d);
		}
	}
}
