/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:50:59 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/05 17:43:09 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	load_portals_texture(t_cub3d *cub3d, t_prtl_sprite *sprite, char *path)
{
	int		i;
	char	*frame_path;
	char	*frame_num;
	char	*temp1;
	char	*temp2;

	// Allouer de la mémoire pour 16 frames d'animation
	sprite->frames = malloc(sizeof(t_texture_img) * 16);
	if (!sprite->frames)
		return (0);
	
	i = 0;
	while (i < 16)
	{
		frame_num = ft_itoa(i);
		if (!frame_num)
			return (0);
		temp1 = ft_strjoin(frame_num, ".xpm");
		temp2 = ft_strjoin("/Portal_", temp1);
		frame_path = ft_strjoin(path, temp2);
		free(frame_num);
		free(temp1);
		free(temp2);
		if (!frame_path || !load_texture(cub3d, &sprite->frames[i], frame_path))
		{
			if (frame_path)
				free(frame_path);
			return (0);
		}
		free(frame_path);
		i++;
	}
	sprite->current_frame = 0;
	sprite->frame_counter = 0;
	sprite->last_frame_time = 0;
	return (1);
}
