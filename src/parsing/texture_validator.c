/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:40:54 by norabino          #+#    #+#             */
/*   Updated: 2025/09/22 18:55:16 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	validate_all_textures(t_cub3d *cub3d, int *idx)
{
	int	i;
	int	result;

	i = 0;
	*idx = 0;
	while (cub3d->file[i])
	{
		result = process_texture_line(cub3d, i);
		if (result != -1)
			*idx = result;
		i++;
	}
	if (!all_text_set(cub3d))
		exit_error("Missing texture(s)", cub3d);
	return (1);
}
