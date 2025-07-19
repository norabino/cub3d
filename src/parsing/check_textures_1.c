/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:58:31 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/19 21:33:01 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_text_extension(t_cub3d *cub3d, char *textures)
{
	char	*ext;
	int		i;

	i = ft_strlen(textures) - 1;
	while (i && textures[i] != '.')
		i--;
	ext = ft_strndup(&textures[i], 4);
	if (!ext || !ft_strcmp(ext, textures))
		exit_error("No file extension.", cub3d);
	if (ft_strcmp(ext, ".xpm"))
		return (0);
	return (1);
}

int	all_text_set(t_textures textures)
{
	if (!textures.north || !textures.south || !textures.west || !textures.east)
		return (0);
	if (!check_text_extension(textures.cub3d, textures.north))
		exit_error("Wrong north texture extension.", textures.cub3d);
	if (!check_text_extension(textures.cub3d, textures.south))
		exit_error("Wrong south texture extension.", textures.cub3d);
	if (!check_text_extension(textures.cub3d, textures.west))
		exit_error("Wrong west texture extension.", textures.cub3d);
	if (!check_text_extension(textures.cub3d, textures.east))
		exit_error("Wrong east texture extension.", textures.cub3d);
	return (1);
}
