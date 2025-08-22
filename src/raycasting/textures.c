/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/08/22 15:58:26 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Nettoie le chemin d'un fichier en enlevant les espaces et retours à la ligne
** Comme effacer la poussière sur une adresse pour bien la lire
*/
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

/*
** Charge UNE texture depuis un fichier XPM
** Comme scanner une photo pour la mettre dans l'ordinateur
** La texture devient utilisable pour décorer les murs
*/
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

/*
** Charge TOUTES les textures des 4 murs (Nord, Sud, Est, Ouest)
** Comme préparer tous les posters qu'on va coller sur les murs
** Si un poster ne marche pas, on arrête tout le programme
*/
void	load_all_textures(t_cub3d *cub3d)
{
	if (!cub3d)
		return ;
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
}

/*
** Libère la mémoire de toutes les textures
** Comme jeter tous les posters quand on déménage
** Important pour éviter les fuites de mémoire
*/
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
}

/*
** Choisit la bonne texture selon la direction du mur
** Nord/Sud/Est/Ouest = textures différentes
** Comme choisir le bon papier peint selon quelle pièce on décore
*/
void	select_wall_texture(t_cub3d *cub3d, t_dda *dda,
	t_texture_calc *tex_calc)
{
	if (!tex_calc)
		return ;
	if (dda->side == 0)
	{
		if (dda->ray_dir_x > 0)
			tex_calc->current_text = &cub3d->textures.west_img;
		else
			tex_calc->current_text = &cub3d->textures.east_img;
	}
	else
	{
		if (dda->ray_dir_y > 0)
			tex_calc->current_text = &cub3d->textures.north_img;
		else
			tex_calc->current_text = &cub3d->textures.south_img;
	}
}
