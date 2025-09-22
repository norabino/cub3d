/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:40:54 by norabino          #+#    #+#             */
/*   Updated: 2025/09/22 18:55:13 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	extract_filename_from_line(char *line, int j, char **filename)
{
	int	len;
	int	i;

	*filename = ft_substr(line, j, ft_strlen(line) - j);
	len = ft_strlen(*filename);
	i = len - 1;
	while (i >= 0 && ((*filename)[i] == ' ' || (*filename)[i] == '\t'
			|| (*filename)[i] == '\n' || (*filename)[i] == '\r'))
	{
		(*filename)[i] = '\0';
		i--;
	}
	return (1);
}

void	process_texture_path_found(t_cub3d *cub3d, int j, int z, int i)
{
	char	*filename;

	extract_filename_from_line(cub3d->file[i], j, &filename);
	if (cub3d->file[i][z] != 'P' && !check_extension(filename, ".xpm"))
	{
		free(filename);
		cub3d->nb_error_line = i;
		cub3d->invalid_arg = ft_strdup(cub3d->file[i]);
		exit_error("Wrong texture file extension", cub3d);
	}
	if (cub3d->file[i][z] == 'P' || try_to_open(filename))
		set_texture(cub3d->file[i][z], j, cub3d->file[i], cub3d);
	else
	{
		free(filename);
		cub3d->invalid_arg = ft_strdup(cub3d->file[i]);
		cub3d->nb_error_line = i;
		exit_error("Wrong texture path", cub3d);
	}
	free(filename);
}

int	all_text_set(t_cub3d *cub3d)
{
	if (!cub3d->textures.north || !cub3d->textures.south
		|| !cub3d->textures.west || !cub3d->textures.east)
		return (0);
	return (1);
}

void	set_texture(char c, int j, char *line, t_cub3d *cub3d)
{
	char	*sub;
	int		len;
	int		i;

	len = ft_strlen(line) - j;
	sub = ft_substr(line, j, len);
	len = ft_strlen(sub);
	i = len - 1;
	while (i >= 0 && (sub[i] == ' ' || sub[i] == '\t'
			|| sub[i] == '\n' || sub[i] == '\r'))
	{
		sub[i] = '\0';
		i--;
	}
	assign_texture(c, sub, cub3d);
}
