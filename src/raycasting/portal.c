/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:20:24 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/16 02:09:38 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*create_portal_path(char *base_path, int frame_num)
{
	char	*result;
	char	*frame_str;
	int		base_len;
	int		frame_len;
	int		total_len;

	frame_str = ft_itoa(frame_num);
	if (!frame_str)
		return (NULL);
	base_len = ft_strlen(base_path);
	frame_len = ft_strlen(frame_str);
	total_len = base_len + 8 + frame_len + 4 + 1;
	result = malloc(total_len);
	if (!result)
	{
		free(frame_str);
		return (NULL);
	}
	ft_strcpy(result, base_path);
	ft_strcat(result, "/Portal_");
	ft_strcat(result, frame_str);
	ft_strcat(result, ".xpm");
	free(frame_str);
	return (result);
}

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

/* Charge la texture d'un portail dans une sprite */
int	load_portal_texture(t_cub3d *cub3d)
{
	if (!try_to_open(cub3d->textures.portals))
		exit_error("Wrong folder for portal sprites", cub3d);
	if (!count_portal_frames_part2(cub3d))
		return (0);
	if (cub3d->prtl_sprites.frame_counter == 0)
		return (0);
	if (!init_portal_arrays(cub3d))
		return (0);
	return (load_portal_textures_part2(cub3d));
}

void	init_prtl_sprites(t_cub3d *cub3d)
{
	if (cub3d->nb_portals > 0)
		load_portal_texture(cub3d);
}
