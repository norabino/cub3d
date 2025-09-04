/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:40:54 by norabino          #+#    #+#             */
/*   Updated: 2025/09/04 16:13:54 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	extract_filename_from_line(char *line, int j, char **filename)
{
	int	len;
	int	i;

	*filename = ft_substr(line, j, ft_strlen(line) - j, 0);
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

int	is_valid_file_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/' || str[i] == '.')
			return (1);
		i++;
	}
	return (0);
}

void	process_texture_path_found(t_cub3d *cub3d, char *line, int j, int z)
{
	char	*filename;

	extract_filename_from_line(line, j, &filename);
	if (is_valid_file_path(filename)
		&& check_extension(cub3d, filename, ".xpm"))
	{
		free(filename);
		assign_texture(line[z], j, line, &cub3d->textures);
	}
	else
		free(filename);
}

int	process_single_texture_line(t_cub3d *cub3d, char **file, int i,
	int *found_all)
{
	if (!(*found_all) && parse_texture_line(cub3d, file[i], &cub3d->textures))
	{
		*found_all = 1;
		return (i + 1);
	}
	else if (*found_all)
		parse_texture_line(cub3d, file[i], &cub3d->textures);
	return (-1);
}

int	all_text_set(t_textures textures)
{
	if (!textures.north || !textures.south || !textures.west
		|| !textures.east)
		return (0);
	if (!check_extension(textures.cub3d, textures.north, ".xpm"))
		exit_error("Wrong north texture extension.", textures.cub3d);
	if (!check_extension(textures.cub3d, textures.south, ".xpm"))
		exit_error("Wrong south texture extension.", textures.cub3d);
	if (!check_extension(textures.cub3d, textures.west, ".xpm"))
		exit_error("Wrong west texture extension.", textures.cub3d);
	if (!check_extension(textures.cub3d, textures.east, ".xpm"))
		exit_error("Wrong east texture extension.", textures.cub3d);
	if (textures.floor && !check_extension(textures.cub3d,
			textures.floor, ".xpm"))
		exit_error("Wrong floor texture extension.", textures.cub3d);
	if (textures.ceiling && !check_extension(textures.cub3d,
			textures.ceiling, ".xpm"))
		exit_error("Wrong ceiling texture extension.", textures.cub3d);
	return (1);
}
