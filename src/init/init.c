/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:24:01 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/18 18:31:44 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_portals(t_cub3d *cub3d)
{
	int	i;

	cub3d->tp_portals = NULL;
	cub3d->prtl_sprites.current_frame = 0;
	cub3d->prtl_sprites.frame_counter = 0;
	cub3d->prtl_sprites.frames = 0;
	cub3d->prtl_sprites.last_frame_time = 0;
	cub3d->prtl_sprites.path = 0;
	cub3d->nb_portals = 0;
	i = 0;
	while (i < 26)
	{
		cub3d->portals[i] = 0;
		i++;
	}
}

static void	init_textures(t_cub3d *cub3d)
{
	cub3d->textures.north = NULL;
	cub3d->textures.south = NULL;
	cub3d->textures.west = NULL;
	cub3d->textures.east = NULL;
	cub3d->textures.floor = NULL;
	cub3d->textures.ceiling = NULL;
	cub3d->textures.portals = NULL;
	ft_bzero(&cub3d->textures.north_img, sizeof(t_txt_i));
	ft_bzero(&cub3d->textures.south_img, sizeof(t_txt_i));
	ft_bzero(&cub3d->textures.west_img, sizeof(t_txt_i));
	ft_bzero(&cub3d->textures.east_img, sizeof(t_txt_i));
	ft_bzero(&cub3d->textures.floor_img, sizeof(t_txt_i));
	ft_bzero(&cub3d->textures.ceiling_img, sizeof(t_txt_i));
	ft_bzero(&cub3d->prtl_sprites, sizeof(t_prtl_sprite));
}

static void	init_mlx(t_cub3d *cub3d)
{
	cub3d->mlx.mlx = NULL;
	cub3d->mlx.img = NULL;
	cub3d->mlx.win = NULL;
}

static void	init_player(t_cub3d *cub3d)
{
	cub3d->player.fov = 0;
	cub3d->player.direction = 0;
	cub3d->player.last_prtl_pos.x = -1;
	cub3d->player.last_prtl_pos.y = -1;
}

void	init(t_cub3d *cub3d)
{
	cub3d->file = NULL;
	cub3d->map = NULL;
	cub3d->invalid_arg = NULL;
	cub3d->nb_error_line = -1;
	init_mlx(cub3d);
	init_player(cub3d);
	init_colors(cub3d);
	init_textures(cub3d);
	init_time(cub3d);
	init_view(cub3d);
	init_mouse(cub3d);
	init_portals(cub3d);
	init_sprites(cub3d);
	ft_bzero(cub3d->input_state, 256);
}
