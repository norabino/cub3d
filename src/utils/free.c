/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/09 21:47:52 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Libère les chemins des textures Nord et Sud */
static void	ft_free_textures_paths(t_textures *textures)
{
	if (textures->north)
		ft_free(textures->north);
	if (textures->south)
		ft_free(textures->south);
	if (textures->west)
		ft_free(textures->west);
	if (textures->east)
		ft_free(textures->east);
	if (textures->ceiling)
		ft_free(textures->ceiling);
	if (textures->floor)
		ft_free(textures->floor);
}

/* Libère les images de la bibliothèque graphique */
static void	ft_free_mlx(t_mlx *mlx)
{
	if (mlx->img && mlx->img->img && mlx->mlx)
	{
		mlx_destroy_image(mlx->mlx, mlx->img->img);
		mlx->img->img = NULL;
	}
	if (mlx->img)
		ft_free(mlx->img);
	if (mlx->win && mlx->mlx)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx->win = NULL;
	}
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
		mlx->mlx = NULL;
	}
}

/* Fonction principale de nettoyage de toute la mémoire */
void	ft_free(t_cub3d *cub3d)
{
	static int	already_freed = 0;

	if (!cub3d || already_freed)
		return ;
	already_freed = 1;
	if (cub3d->nb_portals > 0)
		free_portal_sprites(cub3d);
	free_textures(cub3d);
	ft_free_textures_paths(&cub3d->textures);
	if (cub3d->map)
		free_map(cub3d->map);
	ft_free_mlx(&cub3d->mlx);
	free(cub3d);
	already_freed = 0;
}
