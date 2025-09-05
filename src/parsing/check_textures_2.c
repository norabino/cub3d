/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:40:54 by norabino          #+#    #+#             */
/*   Updated: 2025/09/05 02:58:53 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Extrait le nom de fichier d'une ligne de configuration */
int	extract_filename(char *line, int j, char **filename)
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

/* Vérifie si une chaîne contient un chemin de fichier */
int	is_file_path(char *str)
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

/* Traite une texture trouvée dans le fichier de configuration */
void	process_texture_found(t_cub3d *cub3d, char *line, int j, int z)
{
	char	*filename;

	extract_filename(line, j, &filename);
	if (is_file_path(filename) && check_extension(cub3d, filename, ".xpm"))
	{
		free(filename);
		set_texture(line[z], j, line, &cub3d->textures);
	}
	else
		free(filename);
}

int	process_texture_line(t_cub3d *cub3d, char **file, int i,
	int *found_all)
{
	if (!(*found_all) && check_line(cub3d, file[i], &cub3d->textures))
	{
		*found_all = 1;
		return (i + 1);
	}
	else if (*found_all)
		check_line(cub3d, file[i], &cub3d->textures);
	return (-1);
}

int	ft_check_textures(t_cub3d *cub3d, char **file, int *idx)
{
	int	i;
	int	found_all;
	int	result;

	i = 0;
	*idx = 0;
	found_all = 0;
	while (file[i])
	{
		result = process_texture_line(cub3d, file, i, &found_all);
		if (result != -1)
			*idx = result;
		i++;
	}
	if (!all_text_set(cub3d->textures))
		exit_error("Missing texture", cub3d);
	return (1);
}
