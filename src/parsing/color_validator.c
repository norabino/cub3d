/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:40:54 by norabino          #+#    #+#             */
/*   Updated: 2025/09/15 16:57:48 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Valide toutes les couleurs du fichier de configuration */
int	validate_all_colors(t_cub3d *cub3d, int *idx)
{
	int	i;
	int	j;

	i = 0;
	(*idx) = 0;
	while (cub3d->file[i])
	{
		j = 0;
		skip_spaces(cub3d->file[i], &j);
		if (!cub3d->file[i][j])
		{
			i++;
			continue ;
		}
		if (!is_letter(cub3d->file[i][j]) && cub3d->file[i][j] != '1')
		{
			cub3d->invalid_arg = ft_strdup(cub3d->file[i]);
			cub3d->nb_error_line = i;
			exit_error("Invalid line", cub3d);
		}
		parse_color_line(cub3d, cub3d->file[i], idx, i);
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
		if (i >= 3)
			exit_error("Invalid RGB floor nbs, must be 3", cub3d);
		cub3d->colors.floor[i] = ft_atoi(split[i]);
		if (cub3d->colors.floor[i] < 0 || cub3d->colors.floor[i] > 255)
			exit_error("Wrong floor color args [0-255]", cub3d);
	}
}
