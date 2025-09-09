/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:40:54 by norabino          #+#    #+#             */
/*   Updated: 2025/09/10 00:05:27 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Valide toutes les textures présentes dans le fichier de configuration */
int	validate_all_textures(t_cub3d *cub3d, char **file, int *idx)
{
	int	i;
	int	j;
	int	found_all;
	int	result;

	i = 0;
	*idx = 0;
	found_all = 0;
	while (file[i])
	{
		j = 0;
		skip_spaces(file[i], &j);
		if (!file[i][j])
		{
			i++;
			continue ;
		}
		if (!is_letter(file[i][j]) && !ft_strchr(file[i], '1'))
		{
			cub3d->invalid_arg = ft_strdup(file[i]);
			exit_error("Invalid line", cub3d);
		}
		if (is_letter(file[i][j]))
		{
			result = process_single_texture_line(cub3d, file, i, &found_all);
			if (result != -1)
				*idx = result;
		}
		i++;
	}
	if (!all_text_set(cub3d))
		exit_error("Missing texture(s)", cub3d);
	return (1);
}
