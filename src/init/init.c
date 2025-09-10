/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:24:01 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/10 17:08:47 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_portals(t_cub3d *cub3d)
{
	cub3d->tp_portals = NULL;
	cub3d->prtl_sprites.current_frame = 0;
	cub3d->prtl_sprites.frame_counter = 0;
	cub3d->prtl_sprites.frames = 0;
	cub3d->prtl_sprites.last_frame_time = 0;
	cub3d->prtl_sprites.path = 0;
	cub3d->nb_portals = 0;
}

/* Initialise les valeurs de base de la structure principale */
static void	init_textures(t_cub3d *cub3d)
{
	cub3d->textures.north = NULL;
	cub3d->textures.south = NULL;
	cub3d->textures.west = NULL;
	cub3d->textures.east = NULL;
	cub3d->textures.floor = NULL;
	cub3d->textures.ceiling = NULL;
	cub3d->textures.portals = NULL;
}

/* Initialise les valeurs de base de la structure principale */
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

/* Initialise les paramètres de la souris et du temps */
static void	init_mouse(t_cub3d *cub3d)
{
	cub3d->mouse.x = SCREEN_WIDTH / 2;
	cub3d->mouse.y = SCREEN_HEIGHT / 2;
	cub3d->mouse.last_x = SCREEN_WIDTH / 2;
	cub3d->mouse.captured = 0;
}

static void	init_time(t_cub3d *cub3d)
{
	cub3d->time.last_refresh = 0;
	cub3d->time.fps_last_time = 0;
	cub3d->time.fps_frame_count = 0;
	cub3d->time.current_fps = 0.0;
	cub3d->time.delta_time = 0.0;
}

/* Initialise les couleurs et les touches du clavier */
static void	init_colors(t_cub3d *cub3d)
{
	cub3d->colors.floor[0] = -1;
	cub3d->colors.floor[1] = -1;
	cub3d->colors.floor[2] = -1;
	cub3d->colors.ceiling[0] = -1;
	cub3d->colors.ceiling[1] = -1;
	cub3d->colors.ceiling[2] = -1;
}

static void	init_view(t_cub3d *cub3d)
{
	cub3d->view.plane_x = -1;
	cub3d->view.plane_y = -1;
}

/* Fonction principale d'initialisation */
void	init(t_cub3d *cub3d)
{
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
	ft_bzero(cub3d->input_state, 256);
}
