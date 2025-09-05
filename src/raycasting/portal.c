/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:20:24 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/05 17:59:34 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Vérifie si le joueur est sur un portail */
char	is_portal(t_cub3d *cub3d)
{
	int		pos_x;
	int		pos_y;
	char	map_char;

	pos_x = (int)cub3d->player.pos_x;
	pos_y = (int)cub3d->player.pos_y;
	if (cub3d->player.last_prtl_pos.x != -1
		&& (pos_x != cub3d->player.last_prtl_pos.x
			|| pos_y != cub3d->player.last_prtl_pos.y))
	{
		cub3d->player.last_prtl_pos.x = -1;
		cub3d->player.last_prtl_pos.y = -1;
	}
	map_char = safe_map_access(cub3d, pos_y, pos_x);
	if (is_lowercase(map_char))
		return (map_char);
	return (0);
}

/* Effectue la téléportation du joueur via un portail */
void	teleportation(t_cub3d *cub3d, t_prtl portal)
{
	t_point	new;
	t_point	current_pos;
	double	dist_to_p1;
	double	dist_to_p2;

	current_pos.x = (int)cub3d->player.pos_x;
	current_pos.y = (int)cub3d->player.pos_y;
	if (current_pos.x == cub3d->player.last_prtl_pos.x
		&& current_pos.y == cub3d->player.last_prtl_pos.y)
		return ;
	dist_to_p1 = sqrt(pow(cub3d->player.pos_x - portal.p1.x, 2)
			+ pow(cub3d->player.pos_y - portal.p1.y, 2));
	dist_to_p2 = sqrt(pow(cub3d->player.pos_x - portal.p2.x, 2)
			+ pow(cub3d->player.pos_y - portal.p2.y, 2));
	if (dist_to_p1 < dist_to_p2)
		new = portal.p2;
	else
		new = portal.p1;
	cub3d->player.pos_x = new.x + 0.5;
	cub3d->player.pos_y = new.y + 0.5;
	cub3d->player.last_prtl_pos = new;
}

/* Définit la couleur du sprite d'un portail */
static void	set_portal_color(t_prtl_sprite *sprite, int portal_index)
{
	int	palette[6][3];
	int	color_idx;

	palette[0][0] = 180;
	palette[0][1] = 90;
	palette[0][2] = 90;
	palette[1][0] = 90;
	palette[1][1] = 180;
	palette[1][2] = 90;
	palette[2][0] = 90;
	palette[2][1] = 90;
	palette[2][2] = 140;
	palette[3][0] = 180;
	palette[3][1] = 180;
	palette[3][2] = 90;
	palette[4][0] = 180;
	palette[4][1] = 90;
	palette[4][2] = 180;
	palette[5][0] = 90;
	palette[5][1] = 180;
	palette[5][2] = 180;
	color_idx = portal_index % 6;
	sprite->color_tint[0] = palette[color_idx][0];
	sprite->color_tint[1] = palette[color_idx][1];
	sprite->color_tint[2] = palette[color_idx][2];
}

/* Initialise un seul portail avec ses propriétés */
static void	init_single_portal(t_cub3d *cub3d, int i)
{
	int		j;
	char	*right_path;
	char	*join1;
	char	*join2;
	char	*num_str;

	cub3d->tp_portals[i].sprite.frames = malloc(sizeof(t_texture_img) * 16);
	if (!cub3d->tp_portals[i].sprite.frames)
		return ;
	j = -1;
	while (++j < 16)
	{
		num_str = ft_itoa(j);
		join1 = ft_strjoin(num_str, ".xpm");
		free(num_str);
		num_str = NULL;
		join2 = ft_strjoin("Portal_", join1);
		free(join1);
		join1 = NULL;
		right_path = ft_strjoin(cub3d->textures.portals, join2);
		free(join2);
		join2 = NULL;
		load_texture(cub3d, &cub3d->tp_portals[i].sprite.frames[j], right_path);
		free(right_path);
		right_path = NULL;
	}
	cub3d->tp_portals[i].sprite.current_frame = 0;
	cub3d->tp_portals[i].sprite.frame_counter = 0;
	cub3d->tp_portals[i].sprite.last_frame_time = gettime_ms();
	set_portal_color(&cub3d->tp_portals[i].sprite, i);
}

/* Initialise tous les sprites de portails */
void	init_prtl_sprites(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < cub3d->nb_portals)
	{
		init_single_portal(cub3d, i);
		i++;
	}
}
