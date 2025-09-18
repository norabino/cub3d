/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:00:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/18 17:35:52 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	count_portal_frames(t_cub3d *cub3d)
{
	int		i;
	int		fd;
	char	*full_path;

	i = 0;
	cub3d->prtl_sprites.frame_counter = 0;
	while (i < 100)
	{
		full_path = create_portal_path(cub3d->textures.portals, i);
		if (!full_path)
			return (0);
		fd = open(full_path, O_RDONLY);
		free(full_path);
		if (fd == -1)
			break ;
		close(fd);
		cub3d->prtl_sprites.frame_counter++;
		i++;
	}
	return (1);
}

int	init_portal_arrays(t_cub3d *cub3d)
{
	int	i;

	if (cub3d->prtl_sprites.path || cub3d->prtl_sprites.frames)
		free_portal_paths(cub3d);
	cub3d->prtl_sprites.path = malloc(sizeof(char *)
			* (cub3d->prtl_sprites.frame_counter + 1));
	if (!cub3d->prtl_sprites.path)
		return (0);
	cub3d->prtl_sprites.frames = malloc(sizeof(t_txt_i)
			* cub3d->prtl_sprites.frame_counter);
	if (!cub3d->prtl_sprites.frames)
	{
		free(cub3d->prtl_sprites.path);
		cub3d->prtl_sprites.path = NULL;
		return (0);
	}
	i = 0;
	while (i < cub3d->prtl_sprites.frame_counter)
	{
		cub3d->prtl_sprites.frames[i].img = NULL;
		cub3d->prtl_sprites.frames[i].addr = NULL;
		i++;
	}
	return (1);
}

int	load_portal_texture_bis(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < cub3d->prtl_sprites.frame_counter)
	{
		cub3d->prtl_sprites.path[i] = create_portal_path(
				cub3d->textures.portals, i);
		if (!cub3d->prtl_sprites.path[i])
			return (0);
		if (!load_texture(cub3d, &cub3d->prtl_sprites.frames[i],
				cub3d->prtl_sprites.path[i]))
		{
			free_portal_sprites(cub3d);
			return (0);
		}
		i++;
	}
	cub3d->prtl_sprites.path[cub3d->prtl_sprites.frame_counter] = NULL;
	cub3d->prtl_sprites.current_frame = 0;
	cub3d->prtl_sprites.last_frame_time = 0;
	return (1);
}
