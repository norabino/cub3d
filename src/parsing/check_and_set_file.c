/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_set_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:33:35 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/13 12:09:38 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Définit la direction initiale du joueur selon le caractère */
void	set_direction(t_cub3d *cub3d, char dir)
{
	if (dir == 'N')
	{
		cub3d->player.dir_x = 0;
		cub3d->player.dir_y = -1;
	}
	else if (dir == 'S')
	{
		cub3d->player.dir_x = 0;
		cub3d->player.dir_y = 1;
	}
	else if (dir == 'E')
	{
		cub3d->player.dir_x = 1;
		cub3d->player.dir_y = 0;
	}
	else if (dir == 'W')
	{
		cub3d->player.dir_x = -1;
		cub3d->player.dir_y = 0;
	}
}

/* Vérifie et configure un fichier de configuration */
int	check_and_set_file(t_cub3d *cub3d)
{
	int	idx_line;
	int	tmp;

	idx_line = 0;
	validate_all_textures(cub3d, &idx_line);
	tmp = idx_line;
	validate_all_colors(cub3d, &idx_line);
	if (tmp > idx_line)
		idx_line = tmp;
	ft_check_map(cub3d, &idx_line);
	ft_check_portals(cub3d);
	set_prtls(cub3d);
	set_direction(cub3d, cub3d->player.dir);
	cub3d->player.pos_x = (double)cub3d->player.pos_x + 0.5;
	cub3d->player.pos_y = (double)cub3d->player.pos_y + 0.5;
	cub3d->player.fov = 66;
	return (1);
}
