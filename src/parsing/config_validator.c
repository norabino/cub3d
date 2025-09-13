/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:43:09 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/13 12:01:51 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Valide un fichier de configuration .cub complet */
int	validate_config_file(t_cub3d *cub3d)
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
	cub3d->player.fov = FOV;
	return (1);
}
