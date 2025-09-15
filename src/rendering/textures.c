/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/15 18:14:37 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Nettoie le chemin d'un fichier en enlevant les espaces */
static char	*clean_path(char *path)
{
	int	len;

	if (!path)
		return (NULL);
	len = 0;
	while (path[len])
		len++;
	while (len > 0 && (path[len - 1] == '\n' || path[len - 1] == '\r'
			|| path[len - 1] == ' ' || path[len - 1] == '\t'))
	{
		path[len - 1] = '\0';
		len--;
	}
	return (path);
}

/* Charge une texture depuis un fichier XPM */
int	load_texture(t_cub3d *cub3d, t_texture_img *tex_img, char *path)
{
	char	*clean_path_str;

	if (!cub3d || !tex_img || !path)
		return (0);
	clean_path_str = clean_path(path);
	tex_img->img = mlx_xpm_file_to_image(cub3d->mlx.mlx, clean_path_str,
			&tex_img->width, &tex_img->height);
	if (!tex_img->img)
		return (0);
	tex_img->addr = mlx_get_data_addr(tex_img->img, &tex_img->bits_per_pixel,
			&tex_img->line_length, &tex_img->endian);
	if (!tex_img->addr)
	{
		mlx_destroy_image(cub3d->mlx.mlx, tex_img->img);
		return (0);
	}
	return (1);
}

/* Charge toutes les textures des 4 murs */
void	load_all_textures(t_cub3d *cub3d)
{
	if (!load_texture(cub3d, &cub3d->textures.north_img,
			cub3d->textures.north))
		exit_error("Error: Failed to load north texture", cub3d);
	if (!load_texture(cub3d, &cub3d->textures.south_img,
			cub3d->textures.south))
		exit_error("Error: Failed to load south texture", cub3d);
	if (!load_texture(cub3d, &cub3d->textures.east_img,
			cub3d->textures.east))
		exit_error("Error: Failed to load east texture", cub3d);
	if (!load_texture(cub3d, &cub3d->textures.west_img,
			cub3d->textures.west))
		exit_error("Error: Failed to load west texture", cub3d);
	if (cub3d->textures.floor && !load_texture(cub3d,
			&cub3d->textures.floor_img, cub3d->textures.floor))
		exit_error("Error: Failed to load floor texture", cub3d);
	if (cub3d->textures.ceiling && !load_texture(cub3d,
			&cub3d->textures.ceiling_img, cub3d->textures.ceiling))
		exit_error("Error: Failed to load ceiling texture", cub3d);
}

/* Libère la mémoire de toutes les textures */
void	free_textures(t_cub3d *cub3d)
{
	if (!cub3d || !cub3d->mlx.mlx)
		return ;
	if (cub3d->textures.north_img.img)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->textures.north_img.img);
	if (cub3d->textures.south_img.img)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->textures.south_img.img);
	if (cub3d->textures.east_img.img)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->textures.east_img.img);
	if (cub3d->textures.west_img.img)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->textures.west_img.img);
	if (cub3d->textures.floor_img.img)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->textures.floor_img.img);
	if (cub3d->textures.ceiling_img.img)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->textures.ceiling_img.img);
}

/* Choisit la bonne texture selon la direction du mur */
void	select_wall_texture(t_cub3d *cub3d, t_dda *dda,
	t_texture_calc *tex_calc)
{
		char	map_char;

	if (!tex_calc)
		return ;
	map_char = cub3d->map[(int)dda->map_y][(int)dda->map_x];
	tex_calc->is_portal = 0;
	if (is_lowercase(map_char))
		select_prtl_texture(cub3d, tex_calc, map_char);
	else
		select_wall_normal_texture(cub3d, dda, tex_calc);
}
