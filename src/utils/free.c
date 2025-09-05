/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/05 01:25:54 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Libère les chemins des textures Nord et Sud */
static void	ft_free_textures_paths(t_textures *s_textures)
{
	if (s_textures->north)
	{
		free(s_textures->north);
		s_textures->north = NULL;
	}
	if (s_textures->south)
	{
		free(s_textures->south);
		s_textures->south = NULL;
	}
}

/* Libère les chemins des textures Ouest et Est */
static void	ft_free_textures_paths_two(t_textures *s_textures)
{
	if (s_textures->west)
	{
		free(s_textures->west);
		s_textures->west = NULL;
	}
	if (s_textures->east)
	{
		free(s_textures->east);
		s_textures->east = NULL;
	}
}

/* Libère les images de la bibliothèque graphique */
static void	ft_free_mlx(t_mlx *s_mlx)
{
	if (s_mlx->img && s_mlx->img->img && s_mlx->mlx)
	{
		mlx_destroy_image(s_mlx->mlx, s_mlx->img->img);
		s_mlx->img->img = NULL;
	}
	if (s_mlx->img)
	{
		free(s_mlx->img);
		s_mlx->img = NULL;
	}
}

/* Libère la fenêtre et la connexion graphique */
static void	ft_free_mlx_two(t_mlx *s_mlx)
{
	if (s_mlx->win && s_mlx->mlx)
	{
		mlx_destroy_window(s_mlx->mlx, s_mlx->win);
		s_mlx->win = NULL;
	}
	if (s_mlx->mlx)
	{
		mlx_destroy_display(s_mlx->mlx);
		free(s_mlx->mlx);
		s_mlx->mlx = NULL;
	}
}

/* Fonction principale de nettoyage de toute la mémoire */
void	ft_free(t_cub3d *s_cub3d)
{
	static int	g_already_freed = 0;

	if (!s_cub3d || g_already_freed)
		return ;
	g_already_freed = 1;
	if (s_cub3d->nb_portals > 0)
		free_portal_sprites(s_cub3d);
	free_textures(s_cub3d);
	ft_free_textures_paths(&s_cub3d->textures);
	ft_free_textures_paths_two(&s_cub3d->textures);
	if (s_cub3d->map)
	{
		free_map(s_cub3d->map);
		s_cub3d->map = NULL;
	}
	ft_free_mlx(&s_cub3d->mlx);
	ft_free_mlx_two(&s_cub3d->mlx);
	free(s_cub3d);
	g_already_freed = 0;
}
