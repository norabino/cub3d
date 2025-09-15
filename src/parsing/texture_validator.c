/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:40:54 by norabino          #+#    #+#             */
/*   Updated: 2025/09/15 17:00:39 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Valide toutes les textures présentes dans le fichier de configuration */
int	validate_all_textures(t_cub3d *cub3d, int *idx)
{
	int	i;
	int	j;
	int	found_all;
	int	result;

	i = 0;
	*idx = 0;
	found_all = 0;
	while (cub3d->file[i])
	{
		j = 0;
		skip_spaces(cub3d->file[i], &j);
		if (!cub3d->file[i][j])
		{
			i++;
			continue ;
		}
		if (!is_letter(cub3d->file[i][j]) && (!all_text_set(cub3d)
			&& !all_colors_set(cub3d)))
		{
			cub3d->invalid_arg = ft_strdup(cub3d->file[i]);
			cub3d->nb_error_line = i;
			exit_error("Invalid line", cub3d);
		}
		if (is_letter(cub3d->file[i][j]))
		{
			result = process_single_texture_line(cub3d, i, &found_all);
			if (result != -1)
				*idx = result;
		}
		i++;
	}
	if (!all_text_set(cub3d))
		exit_error("Missing texture(s)", cub3d);
	return (1);
}
