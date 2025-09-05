/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:40:54 by norabino          #+#    #+#             */
/*   Updated: 2025/09/05 16:12:34 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Valide toutes les textures présentes dans le fichier de configuration */
int	validate_all_textures(t_cub3d *cub3d, char **file, int *idx)
{
	int	i;
	int	found_all;
	int	result;

	i = 0;
	*idx = 0;
	found_all = 0;
	while (file[i])
	{
		result = process_single_texture_line(cub3d, file, i, &found_all);
		if (result != -1)
			*idx = result;
		i++;
	}
	printf("%s\n", cub3d->textures.portals);
	if (!all_text_set(cub3d->textures))
		exit_error("Missing texture(s)", cub3d);
	return (1);
}
