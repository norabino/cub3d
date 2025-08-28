/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:20:24 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/29 00:17:52 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	is_portal(t_cub3d *cub3d)
{
	int	pos_x;
	int	pos_y;

	pos_x = (int)cub3d->player.pos_x;
	pos_y = (int)cub3d->player.pos_y;
	if (cub3d->player.last_prtl_pos.x != -1
		&& (pos_x != cub3d->player.last_prtl_pos.x
			|| pos_y != cub3d->player.last_prtl_pos.y))
	{
		cub3d->player.last_prtl_pos.x = -1;
		cub3d->player.last_prtl_pos.y = -1;
	}
	if (is_lowercase(cub3d->map[pos_y][pos_x]))
		return (cub3d->map[pos_y][pos_x]);
	return (0);
}

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
	cub3d->player.last_prtl_pos = new;
	cub3d->player.pos_x = new.x + 0.5;
	cub3d->player.pos_y = new.y + 0.5;
}

void	init_prtl_sprites(t_cub3d *cub3d)
{
	int		i;
	int		j;
	char	path[256];

	i = 0;
	while (i < cub3d->nb_portals)
	{
		j = 0;
		while (j < 4)
		{
			snprintf(path, sizeof(path), "textures/portal/tp%d.xpm", j);
			load_texture(cub3d, &cub3d->tp_portals[i].sprite.frames[j], path);
			j++;
		}
		cub3d->tp_portals[i].sprite.current_frame = 0;
		cub3d->tp_portals[i].sprite.frame_counter = 0;
		cub3d->tp_portals[i].sprite.last_frame_time = gettime_ms();
		cub3d->tp_portals[i].sprite.color_tint[0] = 100 + (rand() % 156);
		cub3d->tp_portals[i].sprite.color_tint[1] = 100 + (rand() % 156);
		cub3d->tp_portals[i].sprite.color_tint[2] = 100 + (rand() % 156);
		i++;
	}
}

void	update_portal_animations(t_cub3d *cub3d)
{
	int		i;
	long	current_time;
	long	frame_duration;

	current_time = gettime_ms();
	frame_duration = 1000 / 60;
	i = 0;
	while (i < cub3d->nb_portals)
	{
		if ((current_time - cub3d->tp_portals[i].sprite.last_frame_time)
			>= frame_duration)
		{
			cub3d->tp_portals[i].sprite.current_frame
				= (cub3d->tp_portals[i].sprite.current_frame + 1) % 4;
			cub3d->tp_portals[i].sprite.last_frame_time = current_time;
		}
		i++;
	}
}

void	free_portal_sprites(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub3d->nb_portals)
	{
		j = 0;
		while (j < 4)
		{
			if (cub3d->tp_portals[i].sprite.frames[j].img)
				mlx_destroy_image(cub3d->mlx.mlx,
					cub3d->tp_portals[i].sprite.frames[j].img);
			j++;
		}
		i++;
	}
}
