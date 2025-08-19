/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:43:09 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/19 15:25:47 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_extension(t_cub3d *cub3d, char *filename)
{
	char	*ext;
	int		i;

	i = ft_strlen(filename) - 1;
	while (i && filename[i] != '.')
		i--;
	ext = ft_strdup(&filename[i]);
	if (!ext || !ft_strcmp(ext, filename))
	{
		if (ext)
			free(ext);
		exit_error("No file extension.", cub3d);
	}
	if (ft_strcmp(ext, ".cub"))
	{
		free(ext);
		exit_error("Wrong file extension.", cub3d);
	}
	free(ext);
	return (1);
}

char	**malloc_file(t_cub3d *cub3d, char *filename)
{
	char	**file;
	char	*s_line;
	int		fd;
	int		nb_lines;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_error("Error when opening file...", cub3d);
	nb_lines = 0;
	s_line = get_next_line(fd);
	while (s_line)
	{
		free(s_line);
		nb_lines++;
		s_line = get_next_line(fd);
	}
	close(fd);
	file = (char **)malloc(sizeof(char *) * (nb_lines + 1));
	if (!file)
		exit_error("Error allocating file memory...", cub3d);
	return (file);
}

char	**open_file(t_cub3d *cub3d, char *filename)
{
	int		fd;
	char	**file;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_error("Error when opening file...", cub3d);
	file = malloc_file(cub3d, filename);
	if (!file)
		exit_error("Error allocating file memory...", cub3d);
	i = 0;
	file[i] = get_next_line(fd);
	while (file[i])
	{
		i++;
		file[i] = get_next_line(fd);
	}
	file[i] = NULL;
	close(fd);
	return (file);
}
